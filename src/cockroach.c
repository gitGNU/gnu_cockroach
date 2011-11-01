/* -*- mode: C -*-
 *
 *       File:         cockroach.c
 *       Date:         Mon Oct 31 14:27:16 CET 2011
 *
 *       GNU cockroach - Main source file.
 *
 */

/* Copyright (C) 2011 Giuseppe Scrivano, Jose E. Marchesi */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "cockroach.h"
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

  pid = roach_spawn_process (ctx, argv[1], argv + 1);
  if (pid < 0)
    error (EXIT_FAILURE, errno, "spawn process");
  for (;;)
    {
       pid_t p = roach_wait (ctx);
       printf ("PID %i %i %i\n", p, roach_get_sc (ctx),
               roach_entering_sc_p (ctx));
    }
  return 0;
}
