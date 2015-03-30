/*
   libroach definitions.

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

#ifndef ROACH_H
# define ROACH_H

# include <config.h>
# include <stddef.h>
# include <sys/types.h>
# include <stdbool.h>
# include "bitmap.h"

enum HOOK_TYPE
{
  HOOK_ENTER = 1,
  HOOK_EXIT,
  HOOK_BOTH
};

struct roach_context_s;

typedef int (*hook_func_t) (struct roach_context_s *ctx, bool enter, void *data);

typedef struct s_hook
{
  struct s_hook *next;

  /* Describe in which cases the hook is valid.  */
  enum HOOK_TYPE type;

  /* Define which syscalls are intercepted.  */
  bitmap_t *syscalls;

  hook_func_t hook;
  void *data;
}
roach_hook_t;

typedef struct roach_context_s
{
  int pid;
  roach_hook_t *hooks;
  int last_syscall;
  bool entering_sc;
}
roach_context_t;

roach_hook_t *roach_make_hook (enum HOOK_TYPE type, int *syscalls,
                               hook_func_t hook, void *data);
void roach_free_hook (roach_hook_t *ctx);

roach_context_t *roach_make_context ();
void roach_free_context (roach_context_t *ctx);

void roach_ctx_add_hook (roach_context_t *ctx, roach_hook_t *hook);
void roach_ctx_rm_hook (roach_context_t *ctx, roach_hook_t *hook);

int roach_rot_function (roach_context_t *ctx, void (*function) (void *),
                        void *data);

pid_t roach_spawn_process (roach_context_t *ctx, char const *exec,
                         char *const *argv);
int roach_wait (roach_context_t *ctx);

bool roach_entering_sc_p (roach_context_t *ctx);

/* Architecture specific functions.  */
long roach_get_sc (roach_context_t *ctx);
long roach_set_sc (roach_context_t *ctx, int syscall);
long roach_get_sc_ret (roach_context_t *ctx);
long roach_set_sc_ret (roach_context_t *ctx, int retval);
long roach_get_sc_arg (roach_context_t *ctx, int arg);
long roach_set_sc_arg (roach_context_t *ctx, int arg, void *data);
int roach_write_mem (roach_context_t *ctx, const char const *data,
                     const char const *addr, size_t len);
int roach_read_mem (roach_context_t *ctx, char *data,
                    const char const *addr, size_t len);

/* Facilities.  */
int roach_syscall_inhibit (roach_context_t *ctx, bool enter, void *data);
int roach_reg_syscall (roach_context_t *ctx, int syscall,
                       hook_func_t hook_func, void *data);

#endif /* !ROACH_H */
