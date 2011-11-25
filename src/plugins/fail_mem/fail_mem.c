/*
  fail mem plugin.

  Copyright (C) 2011 Jose E. Marchesi <jemarch@gnu.org>
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

#include <roach.h>
#include <syscall.h>

struct
fail_mem_s
{
  int counter;
  int fail_at;
  unsigned int request;
  unsigned int current_size;
};

static int
fail_mem (struct roach_context_s *ctx, bool enter, void *datap)
{
  struct fail_mem_s *data = (struct fail_mem_s *) datap;
  long arg0 = roach_get_sc_arg (ctx, 1);

  if (enter && data->counter < data->fail_at)
    {
      if (arg0 > 0)
        data->counter++;

      data->request = arg0;
    }

  if (!enter && data->request == 0)
    {
      data->current_size = roach_get_sc_ret (ctx);
    }

  if (data->counter >= data->fail_at)
    {
      if (enter && arg0 > 0)
        roach_syscall_inhibit (ctx, enter, NULL);

      if (! enter)
        roach_set_sc_ret (ctx, 0);
    }
}

const char *
plugin_get_name ()
{
  return "fail_mem";
}

int
plugin_load (roach_context_t *ctx)
{
  return 0;
}

int
plugin_free (roach_context_t *ctx)
{
  return 0;
}

int
plugin_add (roach_context_t *ctx, const char *options)
{
  struct fail_mem_s *data = malloc (sizeof *data);
  if (data == NULL)
    return -1;

  data->counter = 0;
  data->fail_at = atoi (options);

  if (roach_reg_syscall (ctx, __NR_brk, fail_mem, data) < 0)
    exit (EXIT_FAILURE);

  if (roach_reg_syscall (ctx, __NR_mmap2, fail_mem, data) < 0)
    exit (EXIT_FAILURE);

  return 0;
}
