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

#include <sys/reg.h>
#include "../roach.h"

/* The following constants describe the layout of the USER section of
   the child process bein peek/poked and are used in the
   linux_generic.c file.  They are based on the contents of
   sys/user.h */

#define SC_REG_SIZE 4
#define SC_REG_ADDR  (SC_REG_SIZE * ORIG_EAX)
#define SC_RET_ADDR  (SC_REG_SIZE * EAX)
#define SC_ARG1_ADDR (SC_REG_SIZE * EBX)
#define SC_ARG2_ADDR (SC_REG_SIZE * ECX)
#define SC_ARG3_ADDR (SC_REG_SIZE * EDX)
#define SC_ARG4_ADDR (SC_REG_SIZE * ESI)
#define SC_ARG5_ADDR (SC_REG_SIZE * EDI)

#include "linux_generic.c"
