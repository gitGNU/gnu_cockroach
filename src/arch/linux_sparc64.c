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

/* The sparc linux port does not have a seekable/pokeable USER area,
   so we have to define our own accessor functions.  */

#define ARCH_HAS_GET_SC 1
#define ARCH_HAS_SET_SC 1
#define ARCH_HAS_GET_SC_RET 1
#define ARCH_HAS_SET_SC_RET 1
#define ARCH_HAS_SET_SC_ARG 1
#define ARCH_HAS_GET_SC_ARG 1

long
roach_get_sc (roach_context_t *ctx)
{
  /* XXX */
  return 0;
}

long
roach_set_sc (roach_context_t *ctx, int syscall)
{
  /* XXX */
  return 0;
}

long
roach_get_sc_ret (roach_context_t *ctx)
{
  /* XXX */
  return 0;
}

long
roach_set_sc_ret (roach_context_t *ctx, int retval)
{
  /* XXX */
  return 0;
}

long
roach_set_sc_arg (roach_context_t *ctx, int arg, void *data)
{
  /* XXX */
  return 0;
}

long
roach_get_sc_arg (roach_context_t *ctx, int arg)
{
  /* XXX */
  return 0;
}

#include "linux_generic.c"
