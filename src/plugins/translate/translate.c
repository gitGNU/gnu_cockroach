/*
  translate syscall plugin.

  Copyright (C) 2015 Jose E. Marchesi <jemarch@gnu.org>
  Copyright (C) 2015 Giuseppe Scrivano <gscrivano@gnu.org>

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
#include <errno.h>

const char *
plugin_get_name ()
{
  return "translate";
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

static int
translate_hook (roach_context_t *ctx, pid_t pid, bool enter, void *data)
{
  long args[6];
  size_t i;
  
  struct roach_sc_spec_s *spec1 = (struct roach_sc_spec_s *) data;
  struct roach_sc_spec_s *spec2 = (struct roach_sc_spec_s *) spec1->user;

  if (!enter)
    return 0;
  
  if (!roach_match_scspec (ctx, spec1))
    return 0;

  for (i = 0; i < spec2->nargs; i++)
    switch (spec2->args[i].mod)
      {
      case '@':
        /* Backreference.  */
        args[i] = roach_get_sc_arg (ctx, spec2->args[i].value.word);
        break;
      case '\0':
        /* Long value.  */
        args[i] = spec2->args[i].value.word;
        break;
      default:
        /* Any other kind of argument is unsupported in the rhs of a
           translation.  */
        return -1;
      }

  return roach_syscall_install (ctx, pid, spec2->syscall,
                                spec2->nargs, args);
}

int
plugin_add (roach_context_t *ctx, const char *options)
{
  char *buffer;
  char *ret, *ret2;
  struct roach_sc_spec_s *spec1;
  struct roach_sc_spec_s *spec2;
  size_t i;

  buffer = strdup (options);
  if (buffer == NULL)
    return -1;

  /* Parse the options for this plugin.  The format is:

     SCSPEC1,SCSPEC2

     where SCSPEC1 and SCSPEC2 are syscall specs.  */

  spec1 = malloc (sizeof (*spec1));
  if (spec1 == NULL)
    return -1;

  if (roach_parse_scspec (buffer, spec1, &ret) < 0)
    return -1;

  if (*ret != ',')
    return -1;
  ret++;

  spec2 = malloc (sizeof (*spec2));
  if (spec2 == NULL)
    return -1;

  if (roach_parse_scspec (ret, spec2, &ret2) < 0)
    return -1;

  /* The RHS syscall spec must only contain long values or
     backreferences as its arguments.  */
  for (i = 0; i < spec2->nargs; i++)
    if (spec2->args[i].mod != '\0' && spec2->args[i].mod != '@')
      return -1;

  if (*ret2 != '\0')
    return -1;

  spec1->user = (void *) spec2;
  if (roach_reg_syscall (ctx, spec1->syscall, translate_hook, spec1) < 0)
    return -1;

  free (buffer);
  return 0;
}
