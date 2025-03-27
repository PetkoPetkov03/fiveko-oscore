#ifndef __OSCORE_Q__
#define __OSCORE_Q__
#include "../atomic/aint.h"
#include <stdlib.h>

typedef struct __node__ {
  atomic_int_t id;
  void* content;
  struct __node__* next;
} node;

typedef struct  __os_q__ {
    node* front;
    node* rear;
    size_t size;
} queue;

queue* queue_init();

void push(queue*, void*);

void* pop(queue*);

node* front(queue*);

node* back(queue*);

void queue_destroy(queue**);

#endif // !__OSCORE_Q__
