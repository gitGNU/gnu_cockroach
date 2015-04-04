/*
   libroach core.

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

#include <config.h>

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <hash.h>
#include "roach.h"

roach_hook_t *
roach_make_hook (enum HOOK_TYPE type, int *syscalls, hook_func_t hook,
                 void *data)
{
  int max_sc = 0, *syscall;
  roach_hook_t *r = malloc (sizeof *r);
  if (r == NULL)
    return r;

  r->next = NULL;
  r->type = type;
  r->hook = hook;
  r->data = data;

  for (syscall = syscalls; *syscall != -1; syscall++)
    if (*syscall > max_sc)
      max_sc = *syscall;

  r->syscalls = roach_bitmap_make (max_sc);
  if (r->syscalls == NULL)
    {
      free (r);
      return NULL;
    }

  for (syscall = syscalls; *syscall != -1; syscall++)
    roach_bitmap_set (r->syscalls, *syscall);

  return r;
}

struct process_context_s
{
  pid_t pid;
  bool entering_sc;
  int last_syscall;
};

void
roach_free_hook (roach_hook_t *ctx)
{
  roach_bitmap_free (ctx->syscalls);
  free (ctx);
}

static bool
PID_compare (void const *x, void const *y)
{
  const struct process_context_s *p1 = x;
  const struct process_context_s *p2 = y;
  return p1->pid == p2->pid;
}

static size_t
PID_hash (void const *x, size_t table_size)
{
  const struct process_context_s *p = x;
  return p->pid % table_size;
}

roach_context_t *
roach_make_context ()
{
  roach_context_t *c = malloc (sizeof *c);
  if (c == NULL)
    return c;

  c->hooks = NULL;
  c->entering_sc = hash_initialize (1, NULL, PID_hash,
                                    PID_compare, NULL);

  return c;
}

void
roach_free_context (roach_context_t *ctx)
{
  free (ctx);
}

void
roach_ctx_add_hook (roach_context_t *ctx, roach_hook_t *hook)
{
  hook->next = NULL;

  if (ctx->hooks == NULL)
    ctx->hooks = hook;
  else
    {
      roach_hook_t *it = ctx->hooks;

      while (it->next)
        it = it->next;

      it->next = hook;
    }
}

void
roach_ctx_rm_hook (roach_context_t *ctx, roach_hook_t *hook)
{
  roach_hook_t *prev = NULL, *it = ctx->hooks;
  while (it)
    {
      if (it == hook)
        break;

      prev = it;
      it = it->next;
    }

  if (! it)
    return;

  if (prev)
    prev->next = it->next;
  else
    ctx->hooks = it->next;
}

static void
insert_pid (roach_context_t *ctx, pid_t pid)
{
  struct process_context_s *val = malloc (sizeof *val);

  val->pid = pid;
  val->last_syscall = -1;
  val->entering_sc = false;

  val = hash_insert (ctx->entering_sc, val);
}

int
roach_rot_process (roach_context_t *ctx, char const *exec, char *const *argv)
{
  pid_t pid = fork ();
  long options = PTRACE_O_TRACEEXIT
    | PTRACE_O_TRACEFORK
    | PTRACE_O_TRACEVFORK
    | PTRACE_O_TRACECLONE;
  if (pid == 0)
    {
      if (ptrace (PTRACE_TRACEME, 0, NULL, NULL) < 0)
        exit (EXIT_FAILURE);
      raise (SIGSTOP);
      execvp (exec, argv);
      exit (EXIT_FAILURE);
    }
  else
    {
      waitpid (pid, NULL, 0);

      if (ptrace (PTRACE_SETOPTIONS, pid, NULL, options) < 0)
        error (EXIT_FAILURE, errno, "error setting ptrace options %i", pid);

      if (ptrace (PTRACE_SYSCALL, pid, NULL, NULL) < 0)
        error (EXIT_FAILURE, errno, "waking up process");
    }

  insert_pid (ctx, pid);
  ctx->current_pid = ctx->root_pid = pid;
  return pid;
}

static void
set_last_sc (roach_context_t *ctx, pid_t pid, int syscall)
{
  struct process_context_s key;
  struct process_context_s *val;

  key.pid = pid;
  val = hash_lookup (ctx->entering_sc, &key);
  if (! val)
    error (EXIT_FAILURE, 0, "hash_lookup failure");

  val->last_syscall = syscall;
}

int
roach_get_last_sc (roach_context_t *ctx, pid_t pid)
{
  struct process_context_s key;
  struct process_context_s *val;
  key.pid = pid;
  val = hash_lookup (ctx->entering_sc, &key);
  if (! val)
    error (EXIT_FAILURE, 0, "hash_lookup failure");

  return val->last_syscall;
}

static void
set_entering_sc (roach_context_t *ctx, pid_t pid, bool status)
{
  struct process_context_s key;
  struct process_context_s *val;

  key.pid = pid;
  val = hash_lookup (ctx->entering_sc, &key);
  if (! val)
    error (EXIT_FAILURE, 0, "hash_lookup failure");

  val->entering_sc = status;
}

bool
roach_entering_sc_p (roach_context_t *ctx, pid_t pid)
{
  struct process_context_s key;
  struct process_context_s *val;
  key.pid = pid;
  val = hash_lookup (ctx->entering_sc, &key);
  if (! val)
    error (EXIT_FAILURE, 0, "hash_lookup failure");

  return val->entering_sc;
}

int
roach_wait (roach_context_t *ctx)
{
  pid_t ret;
  int syscall;
  roach_hook_t *hook;
  int status = 0;
  bool entering_sc;
  ret = waitpid (-1, &status, 0);

  /* Exit when the root process ends.  Maybe wait for all processes to end?  */
  if (ret == ctx->root_pid && WIFEXITED (status))
    return 0;

#define IS_EVENT(X) (status >> 8 == (SIGTRAP | (X << 8)))

  if (IS_EVENT (PTRACE_EVENT_FORK)
      || IS_EVENT (PTRACE_EVENT_CLONE)
      || IS_EVENT (PTRACE_EVENT_VFORK))
    {
      pid_t new_pid;
      ptrace (PTRACE_GETEVENTMSG, ret, NULL, &new_pid);
      insert_pid (ctx, new_pid);

      if (ptrace (PTRACE_SYSCALL, ret, NULL, NULL) < 0)
        error (EXIT_FAILURE, errno, "waking up process");
      return 1;
    }

  ctx->current_pid = ret;
  entering_sc = roach_entering_sc_p (ctx, ret);

  /* The syscall in SC could have been modified by an entering hook,
     so we cannot really rely on it.  */
  if (entering_sc)
    {
      syscall = roach_get_sc (ctx);
      set_last_sc (ctx, ret, syscall);
    }
  else
    syscall = roach_get_last_sc (ctx, ret);

  for (hook = ctx->hooks; hook; hook = hook->next)
    {
      if (!entering_sc && hook->type == HOOK_ENTER)
        continue;

      if (entering_sc && hook->type == HOOK_EXIT)
        continue;

      /* What to do with the return code?  */
      if (roach_bitmap_p (hook->syscalls, syscall))        
        hook->hook (ctx, ret, entering_sc, hook->data);
    }

  set_entering_sc (ctx, ret, !entering_sc);

  if (WIFEXITED (status))
    {
      struct process_context_s key;
      key.pid = ret;
      hash_delete (ctx->entering_sc, &key);
    }
  else if (ptrace (PTRACE_SYSCALL, ctx->current_pid, NULL, NULL) < 0)
    error (EXIT_FAILURE, errno, "waking up process");

  return 1;
}

int
roach_reg_syscalls (roach_context_t *ctx, int syscalls[], hook_func_t hook_func,
                    void *data)
{
  roach_hook_t *hook;

  hook = roach_make_hook (HOOK_BOTH, syscalls, hook_func, data);
  if (hook == NULL)
    return -1;

  roach_ctx_add_hook (ctx, hook);
  return 0;
}

int
roach_reg_syscall (roach_context_t *ctx, int syscall, hook_func_t hook_func,
                   void *data)
{
  roach_hook_t *hook;
  int syscalls[] = {syscall, -1};

  return roach_reg_syscalls (ctx, syscalls, hook_func, data);
}

pid_t
roach_ctx_get_pid (roach_context_t *ctx)
{
  return ctx->current_pid;
}
