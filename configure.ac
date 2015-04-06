dnl Process this file with autoconf to produce a configure script.
dnl
dnl Copyright (C) 2015 Giuseppe Scrivano.
dnl Copyright (C) 2015 Jose E. Marchesi.
dnl
dnl This file is free software; as a special exception the author gives
dnl unlimited permission to copy and/or distribute it, with or without
dnl modifications, as long as this notice is preserved.
dnl
dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
dnl implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([GNU cockroach], [0.1], [bug-cockroach@gnu.org])

dnl Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([dist-xz])
AM_CONFIG_HEADER(src/config.h)

# Minimum Autoconf version required.
AC_PREREQ(2.60)

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([src/cockroach.c])

dnl Checks for programs.
# We need a C compiler.
AC_PROG_CC

# Since we use gnulib: gl_EARLY must be called as soon as possible after
# the C compiler is checked.  The others could be later, but we just
# keep everything together.
gl_EARLY
gl_INIT

# Detect the architecture of the host machine and determine whether it
# is a valid one.
AC_CANONICAL_HOST
case ${host} in
     i[[3456]]86-*-linux-*)
	ROACH_ARCH=x86_32;
	AC_DEFINE([ROACH_ARCH_X86_32],[1],[cockroach architecture]);;
     x86_64-*-linux-*)
	ROACH_ARCH=x86_64;
	AC_DEFINE([ROACH_ARCH_X86_64],[1],[cockroach architecture]);;
     sparc64-*-linux-*)
        ROACH_ARCH=sparc64;
	AC_DEFINE([ROACH_ARCH_SPARC64],[1],[cockroach architecture]);;
     *) AC_ERROR([Unsupported architecture "${host}"]) ;;
esac
AC_SUBST([ROACH_ARCH])
AM_CONDITIONAL([ROACH_ARCH_X86_32],[test "$ROACH_ARCH" = "x86_32"])
AM_CONDITIONAL([ROACH_ARCH_X86_64],[test "$ROACH_ARCH" = "x86_64"])
AM_CONDITIONAL([ROACH_ARCH_SPARC64],[test "$ROACH_ARCH" = "sparc64"])

AC_PROG_LIBTOOL
LT_INIT([dlopen])

# GNU help2man creates man pages from --help output; in many cases, this
# is sufficient, and obviates the need to maintain man pages separately.
# However, this means invoking executables, which we generally cannot do
# when cross-compiling, so we test to avoid that (the variable
# "cross_compiling" is set by AC_PROG_CC).
if test $cross_compiling = no; then
  AM_MISSING_PROG(HELP2MAN, help2man)
else
  HELP2MAN=:
fi

# i18n support from GNU gettext.
AM_GNU_GETTEXT([external],[need-ngettext])
AM_GNU_GETTEXT_VERSION([0.17])

AC_CONFIG_FILES([Makefile \
           doc/Makefile \
           lib/Makefile \
           po/Makefile.in \
           src/Makefile \
           src/plugins/Makefile \
           src/plugins/fail_mem/Makefile \
           src/plugins/inhibit/Makefile \
           tests/Makefile \
           testsuite/Makefile \
           testsuite/cockroach.base/Makefile])
AC_OUTPUT
