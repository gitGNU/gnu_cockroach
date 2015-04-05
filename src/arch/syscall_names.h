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
#else
# include <asm/unistd.h>
#endif

#endif /* ROACH_SYSCALL_NAMES_H */
