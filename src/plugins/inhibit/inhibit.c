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
#include <errno.h>

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

static int
inhibit_hook (roach_context_t *ctx, pid_t pid, bool enter, void *data)
{
  struct roach_sc_spec_s *spec = (struct roach_sc_spec_s *) data;

  if (roach_match_scspec (ctx, spec))
    return roach_syscall_inhibit (ctx, pid, enter, spec->user);

  return 0;
}

int
plugin_add (roach_context_t *ctx, const char *options)
{
  char *buffer;
  int syscall;
  char *ret, *end;
  struct roach_sc_spec_s *spec;

  buffer = strdup (options);
  if (buffer == NULL)
    return -1;

  /* Parse the options for this plugin.  The format is:

     SCSPEC,RET_CODE

     where SCSPEC is a syscall spec and RET_CODE is an integer
     expressed in either decimal, hexadecimal and/or octal.  The
     number can be negative.  */

  spec = malloc (sizeof (*spec));
  if (spec == NULL)
    return -1;

  if (roach_parse_scspec (buffer, spec, &ret) < 0)
    return -1;

  if (*ret != ',')
    return -1;

  errno = 0;
  spec->user = (void *) strtol (++ret, &end, 0);
  if (errno == EINVAL || errno == ERANGE || end == ret)
    return -1;

  if (roach_reg_syscall (ctx, spec->syscall, inhibit_hook, spec) < 0)
    exit (EXIT_FAILURE);

  free (buffer);
  return 0;
}
