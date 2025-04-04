#include "que.h"
#include <stdlib.h>
#include <stdio.h>

queue* queue_init()
{
  queue* q = (queue*)malloc(sizeof(queue));

  if(!q) return NULL;

  q->front = q->rear = NULL;

  q->size = 0;

  return q;
}

void push(queue* q, void* value)
{
    if(!q) {
        perror("queue not initialized");
        return;
    }

    node* new_node = (node*)malloc(sizeof(node));

    if(!new_node) {
        perror("node allocation failure");
        return;
    }

    new_node->id = 0;
    new_node->content = value;
    if(q->rear) {
        new_node->id = q->rear->id + 1;
        q->rear->next = new_node;
    }

    q->rear = new_node;

    if(!q->front) {
        q->front = new_node;
    }

    q->size++;
}

node* front(queue* q)
{
  return (q && q->front) ? q->front : NULL;
}

node* rear(queue* q)
{
    return (q && q->rear) ? q->rear : NULL;
}

void* unwrap_node(node* node) {
    return node->content;
}

u32 node_gid(node* node) {
    return node->id;
}

void pop(queue* q)
{
    if(!q && !q->front) {
        perror("pop error");
        return;
    }

    node* temp = q->front;

    q->front = q->front->next;
    if(!q->front) {
        q->rear = NULL;
    }

    free(temp);

    q->size--;
}

void queue_destroy(queue** q)
{
    if(!q && !*q) return;

    node* current = (*q)->front;
    size_t i = 0;

    while(i < (*q)->size && current) {
        node* temp = current;
        current = current->next;
        free(temp);
        i++;
    }

    free(*q);
    *q = NULL;
}
