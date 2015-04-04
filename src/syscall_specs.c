/*
   cockroach: syscall specs.

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

#include "roach.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

int
roach_parse_scspec (const char *str,
                    roach_sc_spec_t *scspec)
{
  /* The format of a SCSPEC is described by the following regexps:

     SCNAME ::= [a-zA-Z_]+
     ARGS   ::= \(ARG(,ARG)*\)
     ARG    ::= *|@NUM|<NUM|>NUM
     NUM    ::= (0x)?[0-9]+

     SCSPEC ::= SCNAME(SCARGS)?
  */

  char *name;
  const char *p = str;
  
  /* Parse the syscall name and translate it into a syscall number.  */
  while ((*p == '_') || (*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))
    p++;
  if (p == str)
    goto error;

  name = alloca (p - str + 1);
  strncpy (name, str, p - str);
  name[p - str] = '\0';
  
  if (get_syscall_by_name (name, &(scspec->syscall)) == -1)
    goto error;
  
  /* Now parse arguments, which are optional.  */
  scspec->nargs = 0;
  if (*p == '(')
    {
      do
        {
          struct roach_sc_spec_arg_s *arg
            = &scspec->args[scspec->nargs++];
          p++;
          if (*p == '*' || *p == '@' || (*p >= '0' && *p <= '9')
              || *p == '-' || *p == '<' || *p == '>')
            {
              int neg = 1;
              if (arg == NULL)
                goto error;
              
              arg->mod = '\0';
              switch (*p)
                {
                case '*':
                  arg->mod = *p++;
                  break;
                case '@':
                case '<':
                case '>':
                  arg->mod = *p++;
                  /* Fallthrough.  */
                default:
                  {
                    char *end;
                    /* Note that strtol with base=0 handles decimal,
                       octal and hexadecimal numeration bases (up to
                       base 36 with Z=35).  */
                    errno = 0;
                    arg->value = strtol (p, &end, 0);
                    if (errno == EINVAL || errno == ERANGE || end == p)
                      goto error;
                    p = end;
                  }
                  break;
                }
            }
          else
            goto error;
        }
      while (*p == ',');

      if (*p != ')')
        goto error;
    }

  return 0;

 error:
  return -1;
}
