#ifndef __OS_CORE_THREADS__
#define __OS_CORE_THREADS__
#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 1024 * 1024
typedef int thread_t;

thread_t thread_create(void (*func)(void*), void* argc);

void thread_join(thread_t* thread);

#endif // !__OS_CORE_THREADS__

