# Makefile for the test directory of GNU cockroach.
#
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

check_PROGRAMS = test_bitmap

AM_CFLAGS = -I../src
LDADD = @LIBINTL@ ../lib/libcockroach.a ../src/libroach.a

test_bitmap_SOURCES = test_bitmap.c

TESTS = $(check_PROGRAMS)
