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

AM_CFLAGS=-I$(srcdir)/../..

plugin_LTLIBRARIES = fail_mem.la
fail_mem_la_SOURCES = fail_mem.c
fail_mem_la_LDFLAGS = -shared -module
