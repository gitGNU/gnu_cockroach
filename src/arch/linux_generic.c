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

#ifndef ARCH_HAS_SYSCALL_INHIBIT

int
roach_syscall_inhibit (roach_context_t *ctx, bool enter, void *data)
{
  /* Use the sys_getpid=20 syscall instead of the original one.
   DATA will be used as return value from the syscall.  */
   if (enter)
    roach_set_sc (ctx, 20);
  else
    roach_set_sc_ret (ctx, (int) data);

   return 0;
}

#endif
