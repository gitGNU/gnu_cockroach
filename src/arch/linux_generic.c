/*
   linux generic hooks

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
#include <string.h>

/* Note that the functions in this file require for the following
   constants to be defined somewhere else:
   
   SC_RET_ADDR: Address of the register containing the syscall return
   value in the child process USER area.

   SC_ARG[1-5]_ADDR: Addresses of the registers containing the
   syscall arguments in the child process USER area.

   These constants get defined if they weren't previously defined:

   OFFSET(x): Macro returning the address of a given word in the child
   process memory.  */

#ifndef OFFSET
# define OFFSET(x) ((long) x & (sizeof (long) - 1))
#endif

#define min(a,b) ((a) < (b) ? (a) : (b))

long
roach_get_sc (roach_context_t *ctx)
{
  if (! ctx->entering_sc)
    return ctx->last_syscall;

  return ptrace (PTRACE_PEEKUSER, ctx->pid, SC_REG_ADDR, syscall);
}

long
roach_set_sc (roach_context_t *ctx, int syscall)
{
  return ptrace (PTRACE_POKEUSER, ctx->pid, SC_REG_ADDR, syscall);
}

long
roach_get_sc_ret (roach_context_t *ctx)
{
  return ptrace (PTRACE_PEEKUSER, ctx->pid, SC_RET_ADDR, 0);
}

long
roach_set_sc_ret (roach_context_t *ctx, int retval)
{
  return ptrace (PTRACE_POKEUSER, ctx->pid, SC_RET_ADDR, retval);
}

long
roach_set_sc_arg (roach_context_t *ctx, int arg, void *data)
{
  int reg_address = 0;
  switch (arg)
    {
    case 1:
      reg_address = SC_ARG1_ADDR;
      break;

    case 2:
      reg_address = SC_ARG2_ADDR;
      break;

    case 3:
      reg_address = SC_ARG3_ADDR;
      break;

    case 4:
      reg_address = SC_ARG4_ADDR;
      break;

    case 5:
      reg_address = SC_ARG5_ADDR;
      break;

    default:
      return -1;
    }

  return ptrace (PTRACE_POKEUSER, ctx->pid, reg_address, data);
}

long
roach_get_sc_arg (roach_context_t *ctx, int arg)
{
  int reg_address = 0;
  switch (arg)
    {
    case 1:
      reg_address = SC_ARG1_ADDR;
      break;

    case 2:
      reg_address = SC_ARG2_ADDR;
      break;

    case 3:
      reg_address = SC_ARG3_ADDR;
      break;

    case 4:
      reg_address = SC_ARG4_ADDR;
      break;

    case 5:
      reg_address = SC_ARG5_ADDR;
      break;

    default:
      return -1;
    }

  return ptrace (PTRACE_PEEKUSER, ctx->pid, reg_address, NULL);
}

int
roach_write_mem (roach_context_t *ctx, const char const *data,
                 const char const *addr, size_t len)
{
  size_t i;
  if (OFFSET (addr))
    {
      long tmp;
      long to_read = min (len, sizeof (long) - OFFSET (addr));
      tmp = ptrace (PTRACE_PEEKDATA, ctx->pid, addr, NULL);

      memcpy (&tmp, data, to_read);

      ptrace (PTRACE_POKEDATA, ctx->pid, addr, tmp);
      len -= to_read;
      data += to_read;
      addr += to_read;
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
      ptrace (PTRACE_POKEDATA, ctx->pid, addr, tmp);
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
      long to_read = min (len, sizeof (long) - OFFSET (addr));
      tmp = ptrace (PTRACE_PEEKDATA, ctx->pid, addr, NULL);

      memcpy (data, &tmp, to_read);

      len -= to_read;
      data += to_read;
      addr += to_read;
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
      memcpy (data, &tmp, len);
    }

  return 0;
}

#ifndef ARCH_HAS_SYSCALL_INHIBIT

int
roach_syscall_inhibit (roach_context_t *ctx, bool enter, void *data)
{
  /* Use the sys_getpid=20 syscall instead of the original one.
   DATA will be used as return value from the syscall.  */
   if (enter)
    roach_set_sc (ctx, 20);
  else
    roach_set_sc_ret (ctx, (long) data);

   return 0;
}

#endif
