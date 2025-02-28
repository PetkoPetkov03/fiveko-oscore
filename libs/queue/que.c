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

  q->id = -1;
  q->stucture = NULL;
  q->next = NULL;

  return q;
}

void push(queue* q)
{
  if(q->id == -1) {
    q->id = 0;
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

  atomic_int_t aint = q->id >= 0 ? q->id : 0;
  int old = atomic_fetch_add(&aint, 1);
  q->next->id = aint;
  q->next->next = NULL;
}

queue* pop(queue** q)
{
  if(!*q) return NULL;

  queue* head = *q;
  *q = (*q)->next;

  return head;
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
