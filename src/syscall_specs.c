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
                    struct roach_sc_spec_s *scspec,
                    char **endp)
{
  /* The format of a SCSPEC is described by the following regexps:

     SCNAME ::= [a-zA-Z_]+
     ARGS   ::= \(ARG(,ARG)*\)
     ARG    ::= *|@NUM|<NUM|>NUM|"STR"|/REGEXP/
     NUM    ::= (0x)?[0-9]+

     SCSPEC ::= SCNAME(SCARGS)?
  */

  char *name;
  char *p = (char *) str;
  
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
              || *p == '-' || *p == '<' || *p == '>'
              || *p == '"' || *p == '/')
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
                case '"':
                case '/':
                  {
                    int escaped = 0;
                    char *q, *buf;

                    arg->mod = *p++;
                    for (escaped = 0, q = p; *p != arg->mod && !escaped; p++)
                      if (*p == '\\')
                        escaped = 1;
                    buf = malloc (p - q + 1);
                    if (!buf)
                      goto error;
                    strncpy (buf, q, p - q);
                    p++;

                    if (arg->mod == '"')
                      arg->value.str = buf;
                    else
                      {
                        if (regcomp (&arg->value.regex, buf,
                                     REG_EXTENDED | REG_NOSUB) != 0)
                          return -1;
                      }
                    
                    break;
                  }
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
                    arg->value.word = strtol (p, &end, 0);
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
      p++;
    }

  if (endp)
    *endp = p;
  return 0;

 error:
  return -1;
}

/* Determine whether the current syscall matches SCSPEC.  */

bool
roach_match_scspec (roach_context_t *ctx,
                    struct roach_sc_spec_s *scspec)
{
  size_t i;

  /* Check the syscall number.  */
  if (roach_get_sc (ctx) != scspec->syscall)
    return 0;

  /* Check the arguments.  */
  for (i = 0; i < scspec->nargs; i++)
    {
      struct roach_sc_spec_arg_s *arg = &scspec->args[i];
      long svalue = arg->value.word;
      long value = roach_get_sc_arg (ctx, i + 1);
      if (value == -1)
        continue;  /* Or return 0?  */

      switch (arg->mod)
        {
        case '*':
        case '@':
          /* Anything goes.  */
          break;
        case '<':
          if (value >= svalue)
            return 0;
          break;
        case '>':
          if (value <= svalue)
            return 0;
          break;
        case '"':
        case '/':
          {
            /* Read the string from the traced process.  */
            char *buf = alloca (255); /* Yes, this sucks.  */
            size_t j;
            for (j = 0; j < 255; j++)
              {
                if (roach_read_mem (ctx, buf + j, (char *) value + j, 1) < 0)
                  return 0;
                if (buf[j] == '\0') break;
              }
            if (buf[j] != '\0') return 0;

            /* Compare it.  */
            if (arg->mod == '"')
              {
                if (strcmp (buf, arg->value.str) != 0)
                  return 0;
              }
            else
              {
                if (regexec (&arg->value.regex, buf, 0, NULL, 0) == REG_NOMATCH)
                  return 0;
              }
            
            break;
          }
        case '\0':
        default:
          if (value != svalue)
            return 0;
          break;
        }
    }

  return 1;
}

