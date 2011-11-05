/*
   linux i386 arch specific hooks

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
#include <string.h>

#include "../cockroach.h"

int
roach_get_sc (roach_context_t *ctx)
{
  if (! ctx->entering_sc)
    return ctx->last_syscall;

  return ptrace (PTRACE_PEEKUSER, ctx->pid, 4 * ORIG_EAX, syscall);
}

int
roach_set_sc (roach_context_t *ctx, int syscall)
{
  return ptrace (PTRACE_POKEUSER, ctx->pid, 4 * ORIG_EAX, syscall);
}

int
roach_set_sc_ret (roach_context_t *ctx, int retval)
{
  return ptrace (PTRACE_POKEUSER, ctx->pid, 4 * EAX, retval);
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

    case 4:
      reg = ESI;
      break;

    case 5:
      reg = EDI;
      break;

    default:
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

    case 4:
      reg = ESI;
      break;

    case 5:
      reg = EDI;
      break;

    default:
      return -1;
    }

  return ptrace (PTRACE_PEEKUSER, ctx->pid, 4 * reg, NULL);
}

#define OFFSET(x) ((unsigned int) x & (sizeof (long) - 1))

int
roach_write_mem (roach_context_t *ctx, const char const *data,
                 const char const *addr, size_t len)
{
  size_t i;
  if (OFFSET (addr))
    {
      long tmp;
      tmp = ptrace (PTRACE_PEEKDATA, ctx->pid, OFFSET (addr), NULL);

      memcpy (&tmp + OFFSET (addr), data, sizeof (long) - OFFSET (addr));

      ptrace (PTRACE_POKEDATA, ctx->pid, OFFSET (addr), tmp);

      len -= sizeof (long) - OFFSET (addr);
      data += sizeof (long) - OFFSET (addr);
      addr += sizeof (long) - OFFSET (addr);
    }

  for (i = 0; i < len / sizeof (long); i++)
    {
      ptrace (PTRACE_POKEDATA, ctx->pid, addr, *((long *) data++));
      len -= sizeof (long);
      addr += sizeof (long);
    }

  if (len)
    {
      long tmp;
      tmp = ptrace (PTRACE_PEEKDATA, ctx->pid, addr, NULL);
      memcpy (&tmp, data, len);
      ptrace (PTRACE_POKEDATA, ctx->pid, sizeof (long), tmp);
    }

  return 0;
}

int
roach_read_mem (roach_context_t *ctx, char *data,
                const char const *addr, size_t len)
{
  size_t i;
  if (OFFSET (addr))
    {
      long tmp;
      tmp = ptrace (PTRACE_PEEKDATA, ctx->pid, OFFSET (addr), NULL);

      memcpy (data, &tmp + OFFSET (addr), sizeof (long) - OFFSET (addr));

      len -= sizeof (long) - OFFSET (addr);
      data += sizeof (long) - OFFSET (addr);
      addr += sizeof (long) - OFFSET (addr);
    }

  for (i = 0; i < len / sizeof (long); i++)
    {
      *((long *) data++) = ptrace (PTRACE_PEEKDATA, ctx->pid,
                                   addr, NULL);
      len -= sizeof (long);
      addr += sizeof (long);
    }

  if (len)
    {
      long tmp;
      tmp = ptrace (PTRACE_PEEKDATA, ctx->pid, addr, NULL);
      memcpy (data, (void *) tmp, len);
    }

  return 0;
}

#include "linux-generic.c"
