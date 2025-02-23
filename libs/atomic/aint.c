#include "aint.h"

int atomic_fetch_add(atomic_int_t* base, int value) 
{
  int old;
  __asm__ volatile (
    "lock xadd %1, %0"
    : "+m" (*base), "=r" (old)
    : "1" (value)
    : "memory"
  );

  return old;
} 

int atomic_fetch_sub(atomic_int_t* base, int value)
{
  return atomic_fetch_add(base, -value); 
}
