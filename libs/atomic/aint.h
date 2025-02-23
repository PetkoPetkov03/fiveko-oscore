#ifndef __OSCORE_ATOMIC_INT__
#define __OSCORE_ATOMIC_INT__

typedef int atomic_int_t;


int atomic_fetch_add(atomic_int_t* base, int value);

int atomic_fetch_sub(atomic_int_t* base, int value);

#endif // !__OSCORE_ATOMIC_INT__

