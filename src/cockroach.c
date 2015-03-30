/*
   cockroach utility.

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

#include <getopt.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <xalloc.h>
#include <closeout.h>
#include <gettext.h>
#define _(str) gettext (str)

#include "roach.h"
#include "plugins.h"

extern char *program_name;

enum
{
  HELP_ARG,
  PLUGIN_ARG,
  PLUGIN_ADD_ARG,
  VERSION_ARG
};

static const struct option long_options[] =
{
  {"help", no_argument, NULL, HELP_ARG},
  {"plugin", required_argument, NULL, PLUGIN_ARG},
  {"plugin-add", required_argument, NULL, PLUGIN_ADD_ARG},
  {"version", no_argument, NULL, VERSION_ARG},
  {NULL, 0, NULL, 0}
};

void
cockroach_print_help (void)
{
  /* TRANSLATORS: --help output, cockroach synopsis.
     no-wrap */
  printf (_("\
Usage: cockroach [OPTION]... PROGRAM [PROGRAM_ARGS]...\n"));

  /* TRANSLATORS: --help output, cockroach short description.
     no-wrap */
  fputs(_("\
Alter the running environment of your program.\n"), stdout);

  puts ("");
  /* TRANSLATORS: --help output, cockroach arguments.
     no-wrap */
  fputs (_("\
      --help                           print a help message and exit.\n\
      --plugin=PLUGIN                  load the plugin file\n\
      --plugin-add=PLUGIN_NAME:OPTIONS add a plugin instance\n\
      --version                        show version and exit.\n"),
         stdout);

  puts ("");
  /* TRANSLATORS: --help output 5+ (reports)
     TRANSLATORS: the placeholder indicates the bug-reporting address
     for this application.  Please add _another line_ with the
     address for translation bugs.
     no-wrap */
  printf (_("\
Report bugs to: %s\n"), PACKAGE_BUGREPORT);
#ifdef PACKAGE_PACKAGER_BUG_REPORTS
  printf (_("Report %s bugs to: %s\n"), PACKAGE_PACKAGER,
          PACKAGE_PACKAGER_BUG_REPORTS);
#endif
#ifdef PACKAGE_URL
  printf (_("%s home page: <%s>\n"), PACKAGE_NAME, PACKAGE_URL);
#else
  printf (_("%s home page: <http://www.nongnu.org/cockroach/>\n"),
          PACKAGE_NAME, PACKAGE);
#endif
  fputs (_("General help using GNU software: <http://www.gnu.org/gethelp/>\n"),
         stdout);
}

void
cockroach_print_version (void)
{
  printf ("%s %s\n",
          program_name,
          VERSION);
  
  /* xgettext: no-wrap */
  puts ("");

  /* It is important to separate the year from the rest of the message,
     as done here, to avoid having to retranslate the message when a new
     year comes around.  */
  printf (_("\
Copyright (C) %s Jose E. Marchesi.\n\
Copyright (C) %s Giuseppe Scrivano.\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n"), "2011-2015", "2011-2015");

  puts (_("\
\n\
Written by Jose E. Marchesi and Giuseppe Scrivano."));
}

int
main (int argc, char **argv)
{
  roach_context_t *ctx = roach_make_context ();
  pid_t pid;
  char c;
  int ret;
  char *child_program_name;
  int max_argc;

  /* Initialization.  */

  set_program_name ("cockroach");
  atexit (close_stdout);
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  /* Process the command line arguments for cockroach.  */
  for (max_argc = 1; max_argc < argc; max_argc++)
    if (argv[max_argc][0] != '-')
      break;
  while ((ret = getopt_long (max_argc,
                             argv,
                             "",
                             long_options,
                             NULL)) != -1)
    {
      c = ret;
      switch (c)
        {
        case HELP_ARG:
          {
            cockroach_print_help ();
            exit (EXIT_SUCCESS);
            break;
          }
        case PLUGIN_ARG:
          {
            plugins_load (ctx, optarg);
            break;
          }
        case PLUGIN_ADD_ARG:
          {
            char *opt;
            char *data = strdup (optarg);
            if (data == NULL)
              exit (EXIT_FAILURE);
            opt = strchr (data, ':');
            if (opt == NULL)
              exit (EXIT_FAILURE);
            *opt = '\0';

            plugins_load_instance (ctx, data, opt + 1);
            free (data);
            break;
          }
        case VERSION_ARG:
          {
            cockroach_print_version ();
            exit (EXIT_SUCCESS);
            break;
          }
        default:
          {
            exit (EXIT_FAILURE);
          }
        }
    }

  /* Get the name of the program to run and spawn the process.  */

  if (optind == argc)
    {
      fputs (_("No kitchen, no fun.\n"), stdout);
      exit (EXIT_SUCCESS);
    }

  child_program_name = argv[optind];

  pid = roach_rot_process (ctx, child_program_name, argv + optind);
  if (pid < 0)
    error (EXIT_FAILURE, errno, "spawn process");

  while (roach_wait (ctx));

  return 0;
}
