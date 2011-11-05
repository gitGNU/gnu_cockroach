# Copyright 2011 Free Software Foundation, Inc.
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


bin_PROGRAMS = cockroach
noinst_LIBRARIES = libroach.a

include_HEADERS = bitmap.h cockroach.h

EXTRA_DIST = arch/linux_generic.c
libroach_a_SOURCES = bitmap.c libroach.c arch/linux_i386.c

cockroach_SOURCES = cockroach.c

cockroach_LDADD = @LIBINTL@ ../lib/libcockroach.a libroach.a

AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_builddir)/lib
