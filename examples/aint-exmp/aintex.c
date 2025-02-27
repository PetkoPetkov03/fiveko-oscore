#include <atomic/aint.h>
#include <stdio.h>
int main(void)
{
  atomic_int_t a = 0;

  for(int i = 0; i < 1000; i++) {
    int b = atomic_fetch_add(&a, i);
    printf("old %d new %d \n", b, a);
  }

  return 0;
}
