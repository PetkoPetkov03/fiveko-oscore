#include "aint.h"

int atomic_fetch_add(atomic_int_t* base, int value) 
{
  int old = value;
  __asm__ volatile (
    "lock xadd %0, %1\n"
    : "+r" (old), "+m" (*base)
    :
    : "memory"
  );

  return old;
} 

int atomic_fetch_sub(atomic_int_t* base, int value)
{
  return atomic_fetch_add(base, -value); 
}

int test_and_set(atomic_int_t* base, int value)
{
  int old = value;

  __asm__ volatile (
    "lock xchg %1, %0\n"
    : "+m" (*base), "+r" (old)
    :
    : "memory"
  );

  return old;
}

boolean_t cmp_swp(atomic_int_t* base, int exp, int value)
{
  unsigned char ret;

  __asm__ volatile (
    " lock\n"
    " cmpxchg %[newval], %[mem]\n"
    " sete %b[ret]"
    : [ret]"=r" (ret), [mem] "+m" (*base), "+a" (exp)
    : [newval]"r" (value)
    : "memory"
  );

  return ret;
}
