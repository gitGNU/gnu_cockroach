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

#include "bitmap.h"
#include <string.h>

#define BUCKET_SIZE (sizeof (unsigned int) * 8)

static size_t
needed_size (size_t size)
{
  sizeof (unsigned int) * ((size + BUCKET_SIZE) / BUCKET_SIZE - 1);
}

bitmap_t *
roach_bitmap_make (size_t size)
{
  bitmap_t *bm = malloc (sizeof *bm);
  if (bm == NULL)
    return NULL;

  bm->size = needed_size (size);

  bm->data = malloc (bm->size);
  if (bm->data == NULL)
    {
      free (bm);
      return NULL;
    }

  bm->size = size;
  memset (bm->data, 0, bm->size);

  return bm;
}

void
roach_bitmap_free (bitmap_t *bm)
{
  free (bm->data);
  free (bm);
}

int
roach_bitmap_set (bitmap_t *bm, size_t ind)
{
  size_t offset, bucket = needed_size (ind);
  if (bucket > bm->size)
    {
      unsigned int *new_data = realloc (bm->data, bucket);
      if (new_data == NULL)
        return -1;

      bm->data = new_data;
      memset (bm->data + bm->size, 0, bucket - bm->size);
      bm->size = bucket;
    }

  offset = ind % (8 * sizeof (unsigned int));
  bm->data[bucket] |= 1 << offset;
  return 0;
}

int
roach_bitmap_unset (bitmap_t *bm, size_t ind)
{
  size_t offset, bucket = needed_size (ind);
  if (bucket > bm->size)
    return 0;

  offset = ind % (8 * sizeof (unsigned int));
  bm->data[bucket] &= ~(1 << offset);
  return 0;
}

int
roach_bitmap_p (bitmap_t * bm, size_t ind)
{
  size_t offset, bucket = needed_size (ind);
  if (bucket > bm->size)
    return 0;

  offset = ind % (8 * sizeof (unsigned int));
  return bm->data[bucket] & (1 << offset);
}

