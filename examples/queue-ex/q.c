#include "../../libs/queue/que.h"
#include <stdio.h>

int main(void)
{
  queue* stack = queue_init();

  push(stack);
  push(stack);
  push(stack);
  
  printf("back id: %d\n", back(stack).id);
  node node = front(stack);
  printf("front id: %d\n", node.id);
  pop(&stack);
  printf("back id: %d\n", back(stack).id);

  queue_destroy(&stack);
  printf("Correct exit\n");
  
  return 0;
}
