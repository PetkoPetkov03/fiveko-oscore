#include "threads.h"
#include <linux/sched.h>
#include <sched.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdint.h>
#include <unistd.h>

thread_t thread_create(void (*func)(void*), void* argc)
{
  printf("done0\n");
  void* stack = malloc(STACK_SIZE);

  if(!stack)
  {
    perror("Failed to allocate stack\n");
    free(stack);
  }
  int flags = CLONE_VM|CLONE_THREAD|CLONE_SIGHAND;

  pid_t id = syscall(SYS_clone3, func, (char*)stack+STACK_SIZE, flags, argc);

  if(id == -1)
  {
    perror("clone failed");
    free(stack);
    return -1;
  }

  return id;
}

void thread_join(thread_t* thread)
{
    printf("join %d\n", wait((int*)thread));
}
