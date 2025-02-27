#ifndef __OSCORE_ATOMIC_INT__
#define __OSCORE_ATOMIC_INT__
#include <stdbool.h>

typedef _Bool boolean_t;

typedef int atomic_int_t;


int atomic_fetch_add(atomic_int_t* base, int value);

int atomic_fetch_sub(atomic_int_t* base, int value);

int test_and_set(atomic_int_t* base, int value);

boolean_t cmp_swp(atomic_int_t* base, int exp, int value);

#endif // !__OSCORE_ATOMIC_INT__

