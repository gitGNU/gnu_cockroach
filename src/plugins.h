/*
   cockroach plugins.

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

#ifndef PLUGINS_H
# define PLUGINS_H

# include "roach.h"

int plugins_load (roach_context_t *ctx, const char *file);
int plugins_load_instance (roach_context_t *ctx, const char *name, const char *options);
int plugins_free (roach_context_t *ctx);

int plugins_load_dir (roach_context_t *ctx, const char *directory);

#endif
