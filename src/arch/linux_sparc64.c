/*
   linux sparc64 arch specific hooks

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

#include "../roach.h"
#include <ucontext.h>

/* The sparc linux port does not have a seekable/pokeable USER area,
   so we have to define our own accessor functions.  */

#define ARCH_HAS_GET_SC 1
#define ARCH_HAS_SET_SC 1
#define ARCH_HAS_GET_SC_RET 1
#define ARCH_HAS_SET_SC_RET 1
#define ARCH_HAS_SET_SC_ARG 1
#define ARCH_HAS_GET_SC_ARG 1

static gregset_t sparc_regs;

static int
get_sparc_reg (roach_context_t *ctx, int offset, long &value)
{
  if (ptrace (PTRACE_GETREGS, roach_ctx_get_pid (ctx), &sparc_regs, 0) == -1)
    return -1;

  *value = (long) regs[offset];
  return 0;
}

static int
set_sparc_reg (roach_context_t *ctx, int offset, long value)
{
  if (ptrace (PTRACE_GETREGS, roach_ctx_get_pid (ctx), &sparc_regs, 0) == -1)
    return -1;

  regs[offset] = (greg_t) value;

  if (ptrace (PTRACE_SETREGS, roach_ctx_get_pid (ctx), &sparc_regs, 0) == -1)
    return -1;

  return 0;
}

long
roach_get_sc (roach_context_t *ctx)
{
  long ret;

  if (get_sparc_reg (ctx, REG_G1, &ret) < 0)
    return -1;
  return ret;
}

long
roach_set_sc (roach_context_t *ctx, int syscall)
{
  return set_sparc_reg (ctx, REG_G1, syscall);
}

long
roach_get_sc_ret (roach_context_t *ctx)
{
  long ret;

  if (get_sparc_reg (ctx, REG_O0, &ret) < 0)
    return -1;
  return ret;
}

long
roach_set_sc_ret (roach_context_t *ctx, int retval)
{
  return set_sparc_reg (ctx, REG_O0, retval);
}

long
roach_set_sc_arg (roach_context_t *ctx, int arg, void *data)
{
  int offset = 0;
  switch (arg)
    {
    case 1:
      offset = REG_O0;
      break;

    case 2:
      offset = REG_O1;
      break;

    case 3:
      offset = REG_O2;
      break;

    case 4:
      offset = REG_O3;
      break;

    case 5:
      offset = REG_O4;
      break;

    case 6:
      offset = REG_O5;
      break;

    default:
      return -1;
    }

  return set_sparc_reg (ctx, offset, data);
}

long
roach_get_sc_arg (roach_context_t *ctx, int arg)
{
  long ret;
  int offset = 0;
  switch (arg)
    {
    case 1:
      offset = REG_O0;
      break;

    case 2:
      offset = REG_O1;
      break;

    case 3:
      offset = REG_O2;
      break;

    case 4:
      offset = REG_O3;
      break;

    case 5:
      offset = REG_O4;
      break;

    case 6:
      offset = REG_O5;
      break;

    default:
      return -1;
    }

  if (get_sparc_reg (ctx, offset, &ret) < 0)
    return -1;
  return ret;
}

#include "linux_generic.c"
