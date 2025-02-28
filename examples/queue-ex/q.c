#include <queue/que.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  queue* stack = queue_init();

  push(stack);
  push(stack);
  push(stack);
  
  queue* a = pop(&stack);
  printf("id: %d\n", a->id);
  free(a);

  queue_destroy(&stack);
  printf("Correct exit\n");
  
  return 0;
}
