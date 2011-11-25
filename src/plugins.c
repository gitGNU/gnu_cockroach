/*
   cockroach utility.

   Copyright (C) 2011 Jose E. Marchesi <jemarch@gnu.org>
   Copyright (C) 2011 Giuseppe Scrivano <gscrivano@gnu.org>

   cockroach is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   GNU Wget is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "roach.h"
#include "plugins.h"

#include <dlfcn.h>

#include <stdio.h>

typedef const char * (*plugin_get_name_hook_t) ();
typedef int (*plugin_load_hook_t) (roach_context_t *ctx);
typedef int (*plugin_free_hook_t) (roach_context_t *ctx);
typedef  int (*plugin_add_hook_t) (roach_context_t *ctx, const char *options);

static struct plugins_s
{
  struct plugins_s *next;
  void *handle;
  const char *name;
} *plugins = NULL;

int
plugins_load (roach_context_t *ctx, const char *file)
{
  plugin_get_name_hook_t name_hook;
  plugin_load_hook_t load_hook;

  struct plugins_s *p = malloc (sizeof (*p));  
  if (p == NULL)
    return -1;

  p->handle = dlopen (file, RTLD_LAZY);
  if (p->handle == NULL)
    {
      fprintf (stderr, "dlopen: %s\n", dlerror ());
      goto fail;
    }

  name_hook = dlsym (p->handle, "plugin_get_name");
  if (name_hook == NULL)
    goto fail;

  p->name = name_hook ();
  if (p->name == NULL)
    goto fail;

  load_hook = dlsym (p->handle, "plugin_load");
  if (load_hook == NULL)
    goto fail;

  if (load_hook (ctx) < 0)
    goto fail;

  p->next = plugins;
  plugins = p;

  return 0;

 fail:
  free (p);
  return -1;
}

int
plugins_load_instance (roach_context_t *ctx, const char *name, const char *options)
{
  struct plugins_s *it = plugins;
  while (it)
    {
      if (! strcasecmp (it->name, name))
        {
          plugin_add_hook_t add_hook = dlsym (it->handle, "plugin_add");
          if (add_hook == NULL)
            return -1;

          return add_hook (ctx, options);
        }

      it = it->next;
    }

  return -1;
}

int
plugins_free (roach_context_t *ctx)
{
  struct plugins_s *it = plugins;
  while (it)
    {
      plugin_free_hook_t free_hook;
      struct plugins_s *p = it;
      it = it->next;

      free_hook = dlsym (p->handle, "plugin_free");
      if (free_hook)
        free_hook (ctx);

      dlclose (p->handle);
      free (p);
    }

}
