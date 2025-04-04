#ifndef __OSCORE_Q__
#define __OSCORE_Q__
#include "../atomic/aint.h"
#include <stdlib.h>
#include <inttypes.h>

typedef uint32_t u32;

typedef struct __node__ {
    u32 id;
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

void pop(queue*);

node* front(queue*);

node* rear(queue*);;

u32 node_gid(node*);

void* unwrap_node(node*);

void queue_destroy(queue**);

#endif // !__OSCORE_Q__
