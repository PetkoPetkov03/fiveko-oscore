#ifndef __OSCORE_Q__
#define __OSCORE_Q__
#include "../atomic/aint.h"

typedef struct  __os_q__ {
  atomic_int_t id;
  void* stucture;
  struct __os_q__* next;
} queue;

queue* queue_init();

void push(queue*);

queue* pop(queue**);

void queue_destroy(queue**);

#endif // !__OSCORE_Q__
