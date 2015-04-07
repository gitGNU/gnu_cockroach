/*
   tests for the bitmap data structure.

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

#include <dejagnu.h>
#include <bitmap.h>

static int
test_bitmap_make ()
{
  size_t i;
  for (i = 2; i < 1 << 6; i *= 2)
    {
      bitmap_t *bm = roach_bitmap_make (i);
      if (bm == NULL)
        return 1;

      if (bm->n_elements != i)
        return 1;

      if (bm->data == NULL)
        return 1;

      roach_bitmap_free (bm);
    }

  return 0;
}

static int
test_bitmap_set ()
{
  size_t i;
  const size_t n_elements = 512;
  bitmap_t *bm = roach_bitmap_make (n_elements);
  if (bm == NULL)
    return 1;

  for (i = 0; i < n_elements; i++)
    {
      roach_bitmap_set (bm, i);

      if (! roach_bitmap_p (bm, i))
        return 1;

      roach_bitmap_unset (bm, i);

      if (roach_bitmap_p (bm, i))
        return 1;
    }

  roach_bitmap_free (bm);
  return 0;
}

static int
test_bitmap_flip ()
{
  size_t i;
  const size_t n_elements = 512;
  bitmap_t *bm = roach_bitmap_make (n_elements);
  if (bm == NULL)
    return 1;

  for (i = 0; i < n_elements; i++)
    {
      roach_bitmap_flip (bm, i);

      if (! roach_bitmap_p (bm, i))
        return 1;

      roach_bitmap_flip (bm, i);

      if (roach_bitmap_p (bm, i))
        return 1;
    }

  roach_bitmap_free (bm);
  return 0;
}


static int
test_bitmap_flip_all ()
{
  size_t i;
  const size_t n_elements = 512;
  bitmap_t *bm = roach_bitmap_make (n_elements);
  if (bm == NULL)
    return 1;

  for (i = 0; i < n_elements; i++)
    {
      roach_bitmap_flip (bm, i);

      if (! roach_bitmap_p (bm, i))
        return 1;

      roach_bitmap_flip_all (bm);

      if (roach_bitmap_p (bm, i))
        return 1;

      roach_bitmap_flip (bm, i);

      if (! roach_bitmap_p (bm, i))
        return 1;

      roach_bitmap_flip_all (bm);
      if (roach_bitmap_p (bm, i))
        return 1;
    }

  roach_bitmap_free (bm);
  return 0;
}

int
main ()
{
#define TEST(x) if (x == 0) pass(#x); else fail(#x)
  TEST (test_bitmap_make ());
  TEST (test_bitmap_set ());
  TEST (test_bitmap_flip ());

  totals ();
  return failed;
}
