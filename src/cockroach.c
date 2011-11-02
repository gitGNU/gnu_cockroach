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

static int
intercept_read (roach_context_t *ctx, bool enter, void *data)
{
  printf ("%s Read!\n", enter ? "Entering" : "Exiting");
}

int
main (int argc, char *const *argv)
{
  int syscalls[] = {3, 0};
  roach_context_t *ctx = roach_make_context ();
  pid_t pid;
  roach_hook_t *hook = roach_make_hook (HOOK_BOTH, syscalls,
                                        intercept_read, NULL);

  if (argc == 1)
    exit (EXIT_FAILURE);

  roach_ctx_add_hook (ctx, hook);

  pid = roach_spawn_process (ctx, argv[1], argv + 1);
  if (pid < 0)
    error (EXIT_FAILURE, errno, "spawn process");

  for (;;)
    roach_wait (ctx);
  return 0;
}
