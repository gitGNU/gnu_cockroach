/*
   cockroach: system calls management.

   Copyright (C) 2015 Jose E. Marchesi <jemarch@gnu.org>
   Copyright (C) 2015 Giuseppe Scrivano <gscrivano@gnu.org>

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
#include <hash.h>
#include <string.h>

static Hash_table *syscall_names;

struct syscall_entry
{
  const char *name;
  int syscall;
};

static bool
SC_compare (void const *x, void const *y)
{
  const struct syscall_entry *s1 = x;
  const struct syscall_entry *s2 = y;
  return !strcmp (s1->name, s2->name);
}

static size_t
SC_hash (void const *x, size_t table_size)
{
  const struct syscall_entry *s = x;
  return hash_string (s->name, table_size);
}

static int
register_name (const char *name, int value)
{
  struct syscall_entry *entry = malloc (sizeof *entry);
  if (entry == NULL)
    return -1;

  entry->name = strdup (name);
  if (entry->name == NULL)
    return -1;

  entry->syscall = value;
  if (hash_insert (syscall_names, entry) == NULL)
    return -1;

  return 0;
}

int
syscall_names_initialize ()
{
  syscall_names = hash_initialize (200, NULL, SC_hash, SC_compare, NULL);
  if (syscall_names == NULL)
    return -1;

#include "syscall_names.c.inc"

  return 0;
}

int
get_syscall_by_name (const char *name, int *ret)
{
  struct syscall_entry key, *val;

  key.name = name;
  val = hash_lookup (syscall_names, &key);
  if (val == NULL)
    return 0;

  *ret = val->syscall;
  return 0;
}
