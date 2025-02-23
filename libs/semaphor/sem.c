#include "sem.h"
#include <stdlib.h>
#include <sys/ipc.h>

sem_t* semaphor_init(key_t key)
{
  sem_t* semaphor = (sem_t*)malloc(sizeof(sem_t));

  return semaphor;
}
