# Makefile for the test directory of GNU cockroach.
#
# Copyright (c) 2011-2015 Jose E. Marchesi
# Copyright (c) 2011-2015 Giuseppe Scrivano
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

check_PROGRAMS = test_bitmap test_scspecs

# Note that the gnu89 inline semantics are needed for dejagnu.h.
AM_CFLAGS = -I$(top_srcdir)/src -fgnu89-inline
LDADD = @LIBINTL@ $(top_builddir)/src/libroach.la $(top_builddir)/lib/libcockroach.la

test_bitmap_SOURCES = test_bitmap.c
test_bitmap_LDFLAGS = -ldl

test_scspecs_SOURCES = test_scspecs.c
test_scspecs_LDFLAGS = -ldl

TESTS = $(check_PROGRAMS)
