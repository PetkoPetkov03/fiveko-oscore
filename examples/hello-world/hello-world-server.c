#include "../../libs/atomic/aint.h"
#include <stdio.h>

int main(void)
{
  atomic_int_t atomic_num = 0;

  for(int i = 0; i < 10; i++)
  {
    int a = atomic_fetch_add(&atomic_num, i);

    printf("old %d new %d\n", a, atomic_num);
  }

  return 0;
}
