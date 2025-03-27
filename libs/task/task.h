#ifndef __OS_TASK__
#define __OS_TASK__
#include <ucontext.h>
#include "../queue/que.h"

typedef struct task_t {
    ucontext_t context;
    void (*func)();
} task_t;

int create_task(void (*start_routine)());

int task_flush(void);

#endif
