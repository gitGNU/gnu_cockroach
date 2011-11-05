/*
   bitmap data structure.

   Copyright (C) 2011 Jose E. Marchesi <jemarch@gnu.org>
   Copyright (C) 2011 Giuseppe Scrivano <gscrivano@gnu.org>

   cockroach is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   GNU Wget is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COCKROACH_BITMAP_H
# define COCKROACH_BITMAP_H

# include <stdlib.h>

typedef struct bitmap_s
{
  size_t size;
  size_t n_elements;
  unsigned int *data;
} bitmap_t;

bitmap_t *roach_bitmap_make (size_t);
void roach_bitmap_free (bitmap_t *);
int roach_bitmap_set (bitmap_t *, size_t);
int roach_bitmap_unset (bitmap_t *, size_t);
int roach_bitmap_p (bitmap_t *, size_t);
int roach_bitmap_flip (bitmap_t *, size_t);
int roach_bitmap_flip_all (bitmap_t *);

#endif
