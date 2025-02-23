#ifndef __OSCORE_SEMAPHOR__
#define __OSCORE_SEMAPHOR__
#include <sys/ipc.h>
#include <sys/shm.h>

enum SEM_SIGNAL {
  WAIT,
  RELEASE,
};

typedef struct __sem_t__ {
  int sm_id;
  void* sm;
  enum SEM_SIGNAL signal;
} sem_t;

sem_t* semapthor_init(key_t key);
  
#endif // !
