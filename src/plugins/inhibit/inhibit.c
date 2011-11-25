/*
  inhibit syscall plugin.

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

#include <roach.h>

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
  int syscall = atoi (options);

  if (roach_reg_syscall (ctx, syscall, roach_syscall_inhibit, (void *) -1) < 0)
    exit (EXIT_FAILURE);

  return 0;
}
