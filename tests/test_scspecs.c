/*
  tests for the syscall specs parser.

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

#include <roach.h>
#include <syscall.h>

roach_sc_spec_t spec;

int
test_name_only (void)
{
  if (roach_parse_scspec ("write", &spec) < 0)
    return -1;
  if (spec.syscall != __NR_write)
    return -1;
  if (spec.nargs != 0)
    return -1;

  return 0;
}

int
test_name_and_one_arg (void)
{
  if (roach_parse_scspec ("write(1)", &spec) < 0)
    return -1;  
  if (spec.syscall != __NR_write)
    return -1;
  if (spec.nargs != 1)
    return -1;
  if (spec.args[0].value != 1)
    return -1;

  return 0;
}

int
test_name_and_two_args (void)
{
  if (roach_parse_scspec ("write(1,20)", &spec) < 0)
    return -1;  
  if (spec.syscall != __NR_write)
    return -1;
  if (spec.nargs != 2)
    return -1;
  if (spec.args[0].value != 1)
    return -1;
  if (spec.args[1].value != 20)
    return -1;

  return 0;
}

int
test_name_hex_args (void)
{
  if (roach_parse_scspec ("write(0xa,0xb)", &spec) < 0)
    return -1;  
  if (spec.syscall != __NR_write)
    return -1;
  if (spec.nargs != 2)
    return -1;
  if (spec.args[0].value != 10)
    return -1;
  if (spec.args[1].value != 11)
    return -1;

  return 0;
}

int
test_name_any_args (void)
{
  if (roach_parse_scspec ("write(*,0xb)", &spec) < 0)
    return -1;
  if (spec.syscall != __NR_write)
    return -1;
  if (spec.nargs != 2)
    return -1;
  if (spec.args[0].mod != '*')
    return -1;
  if (spec.args[1].value != 11)
    return -1;

  return 0;
}

int
test_name_backrefs_args (void)
{
  if (roach_parse_scspec ("write(*,0xb,@2)", &spec) < 0)
    return -1;
  if (spec.syscall != __NR_write)
    return -1;
  if (spec.nargs != 3)
    return -1;
  if (spec.args[0].mod != '*')
    return -1;
  if (spec.args[1].value != 11)
    return -1;
  if (spec.args[2].mod != '@')
    return -1;
  if (spec.args[2].value != 2)
    return -1;

  return 0;
}

int
test_name_comparison_args (void)
{
  if (roach_parse_scspec ("write(*,<0xb,>2)", &spec) < 0)
    return -1;
  if (spec.syscall != __NR_write)
    return -1;
  if (spec.nargs != 3)
    return -1;
  if (spec.args[0].mod != '*')
    return -1;
  if (spec.args[1].mod != '<')
    return -1;
  if (spec.args[1].value != 11)
    return -1;
  if (spec.args[2].mod != '>')
    return -1;
  if (spec.args[2].value != 2)
    return -1;

  return 0;
}

/*
  printf ("XXX: spec.syscall: %d\n", spec.syscall);
  printf ("XXX: spec.nargs: %d\n", spec.nargs);
  printf ("XXX: spec.args[0].mod: %c\n", spec.args[0].mod);
  printf ("XXX: spec.args[0].value: %ld\n", spec.args[0].value);
*/

int
main ()
{
  syscall_names_initialize ();
  
#define TEST(x) if ((x) == -1) return 1
  TEST(test_name_only());
  TEST(test_name_and_one_arg());
  TEST(test_name_and_two_args());
  TEST(test_name_hex_args());
  TEST(test_name_any_args());
  TEST(test_name_backrefs_args());
  TEST(test_name_comparison_args());
  return 0;
}
