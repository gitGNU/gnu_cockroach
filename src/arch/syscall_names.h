/*
   Syscall names for cockroach.

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

#ifndef ROACH_SYSCALL_NAMES_H
#define ROACH_SYSCALL_NAMES_H

#include <config.h>

#ifdef ROACH_ARCH_SPARC64
# include "sparc_syscall_names.h"
#elif ROACH_ARCH_X86_32
# define __SYSCALL_I386(x,y,z) __SYSCALL(x, y)
# include "x86_32_syscalls.h"
#elif ROACH_ARCH_X86_64
# define __SYSCALL_X32(x,y,z) __SYSCALL(x, y)
# define __SYSCALL_32(x,y,z) __SYSCALL(x, y)
# define __SYSCALL_64(x,y,z) __SYSCALL(x, y)
# define __SYSCALL_COMMON(x,y,z) __SYSCALL(x, y)
# include "x86_64_syscalls.h"
#else
# include <asm/unistd.h>
#endif

#endif /* ROACH_SYSCALL_NAMES_H */
