#include <threads/threads.h>
#include <stdio.h>
#include <unistd.h>

void test(void* a)
{
  printf("test %d\n", *(int*)a);
}

void test2()
{
  printf("test2\n");
}

int main(void)
{
  int a = 12;
  thread_t t_id = thread_create(&test, &a);
  printf("tid: %d\n", t_id);

  thread_join(&t_id);
  return 0;
}
