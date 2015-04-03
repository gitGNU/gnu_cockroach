/*
  inhibit syscall plugin.

  Copyright (C) 2011-2015 Jose E. Marchesi <jemarch@gnu.org>
  Copyright (C) 2011-2015 Giuseppe Scrivano <gscrivano@gnu.org>

  cockroach is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  cockroach is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <roach.h>
#include <stdlib.h>
#include <string.h>

const char *
plugin_get_name ()
{
  return "inhibit";
}

int
plugin_load (roach_context_t *ctx)
{
  return 0;
}

int
plugin_free (roach_context_t *ctx)
{
  return 0;
}

int
plugin_add (roach_context_t *ctx, const char *options)
{
  char *buffer;
  int syscall;
  char *ret;
  void *ret_code;

  buffer = strdup (options);
  if (buffer == NULL)
    return -1;

  ret = strchr (buffer, ',');
  if (ret)
    {
      *ret = '\0';
      ret++;
    }
  if (ret)
    ret_code = (void *) atol (ret);
  else
    ret_code =(void *) -1;

  if (get_syscall_by_name (buffer, &syscall) < 0)
    syscall = atoi (buffer);

  if (roach_reg_syscall (ctx, syscall, roach_syscall_inhibit, ret_code) < 0)
    exit (EXIT_FAILURE);

  free (buffer);
  return 0;
}
