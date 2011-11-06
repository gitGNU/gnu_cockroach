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
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int
main (int argc, char *const *argv)
{
  roach_context_t *ctx = roach_make_context ();
  pid_t pid;

  if (argc == 1)
    exit (EXIT_FAILURE);

  if (roach_reg_syscall (ctx, 4, roach_syscall_inhibit, (void *) -1) < 0)
    exit (EXIT_FAILURE);

  pid = roach_spawn_process (ctx, argv[1], argv + 1);
  if (pid < 0)
    error (EXIT_FAILURE, errno, "spawn process");

  for (;;)
    {
      int status;
      roach_wait (ctx, &status);
      if (WIFEXITED (status))
        break;
    }

  return 0;
}
