#include <unistd.h>

int
main ()
{
  write (1, "foo\n", 4);
  return 0;
}
