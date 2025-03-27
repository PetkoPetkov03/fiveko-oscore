#include "que.h"
#include <stdlib.h>
#include <stdio.h>

queue* queue_init()
{
  queue* q = (queue*)malloc(sizeof(queue));

  if(!q) {
    perror("failed queue initialization");
    exit(EXIT_FAILURE);
  }

  node node_v = {
    -1,
    NULL
  };

  q->node_v = node_v;
  q->next = NULL;

  return q;
}

void push(queue* q, void* value)
{
  if(q->node_v.id == -1) {
    node node_v = {
      0,
      value
    };

    q->node_v = node_v;
    return;
  }

  while(q->next != NULL) {
    q = q->next;
  }

  q->next = (queue*)malloc(sizeof(queue));
  if(!q->next) {
    perror("push memory allocation failed!");
    exit(EXIT_FAILURE);
  }

  int aint = q->node_v.id + 1;
  node node_v = {
    aint,
    value,
  };

  q->next->node_v = node_v;
  q->next->next = NULL;
}

node front(queue* q)
{
  return q->node_v;
}

node back(queue* q)
{
  queue* head = q;

  while(head->next) {
    head = head->next;
  }

  return head->node_v;
}

void pop(queue** q)
{
  queue* head = *q;
  *q = (*q)->next;

  free(head);
}

void queue_destroy(queue** q)
{
  queue* head = *q;
  while(head) {
    queue* temp = head;
    head = head->next;
    free(temp);
  }

  *q = NULL;
}
