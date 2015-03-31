# Copyright 2011-2015 Giuseppe Scrivano.
# Copyright 2011-2015 Jose E. Marchesi.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

include $(top_srcdir)/Makefile.am.common

bin_PROGRAMS = cockroach
inst_LTLIBRARIES = libroach.la

SUBDIRS = plugins

instdir=@libdir@/roach/

include_HEADERS = bitmap.h roach.h plugins.h

EXTRA_DIST = arch/linux_generic.c arch/linux_i386.c arch/linux_x86_64.c
libroach_la_SOURCES = bitmap.c roach.c plugins.c

libroach_la_LDFLAGS = -shared

if ROACH_ARCH_X86_32
   libroach_la_SOURCES += arch/linux_i386.c
endif

if ROACH_ARCH_X86_64
   libroach_la_SOURCES += arch/linux_x86_64.c
endif

cockroach_SOURCES = cockroach.c

cockroach_LDFLAGS = -ldl

cockroach_LDADD = @LIBINTL@ $(top_builddir)/lib/libcockroach.la libroach.la
cockroach_LDADD = @LIBINTL@ ../lib/libcockroach.la libroach.la

AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_builddir)/lib \
              -DLOCALEDIR=\"$(localedir)\" -DPLUGINDIR=\"$(plugindir)\"
