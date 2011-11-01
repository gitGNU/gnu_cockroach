/*
   i386 arch specific hooks

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

#include <sys/ptrace.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/reg.h>

#include "../cockroach.h"

int
roach_get_sc (roach_context_t *ctx)
{
  return ptrace (PTRACE_PEEKUSER, ctx->pid, 4 * ORIG_EAX, syscall);
}

int
roach_set_sc (roach_context_t *ctx, int syscall)
{
  return ptrace (PTRACE_POKEUSER, ctx->pid, 4 * ORIG_EAX, syscall);
}

int
roach_set_sc_arg (roach_context_t *ctx, int arg, void *data)
{
  int reg = 0;
  switch (arg)
    {
    case 1:
      reg = EBX;
      break;

    case 2:
      reg = ECX;
      break;

    case 3:
      reg = EDX;
      break;

    default:
      /* TODO */
      return -1;
    }

  return ptrace (PTRACE_POKEUSER, ctx->pid, 4 * reg, data);
}

int
roach_get_sc_arg (roach_context_t *ctx, int arg)
{
  int reg = 0;
  switch (arg)
    {
    case 1:
      reg = EBX;
      break;

    case 2:
      reg = ECX;
      break;

    case 3:
      reg = EDX;
      break;

    default:
      /* TODO */
      return -1;
    }

  return ptrace (PTRACE_POKEUSER, ctx->pid, 4 * reg, NULL);
}

int
roach_write_mem (roach_context_t *ctx, const void const *data, size_t len)
{
  /* TODO */
}

int
roach_read_mem (roach_context_t *ctx, void *data, size_t len)
{
  /* TODO */
}

int
roach_syscall_inhibit (roach_context_t *ctx, void *data)
{
  /* TODO */
}
