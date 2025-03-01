#ifndef __OSCORE_Q__
#define __OSCORE_Q__
#include "../atomic/aint.h"

typedef struct __node__ {
  atomic_int_t id;
  void* content;
} node;

typedef struct  __os_q__ {
  struct __node__ node_v; 
  struct __os_q__* next;
} queue;

queue* queue_init();

void push(queue*);

void pop(queue**);

node front(queue*);

node back(queue*);

void queue_destroy(queue**);

#endif // !__OSCORE_Q__
