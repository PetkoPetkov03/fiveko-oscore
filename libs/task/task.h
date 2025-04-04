#ifndef __OS_TASK__
#define __OS_TASK__
#include <ucontext.h>
#include "../queue/que.h"

typedef struct task_t {
    ucontext_t context;
    void (*func)();
} task_t;

int create_task(void (*start_routine)());

int switch_task();

int task_flush(void);

int test_tasks(void);

int task_exec();

task_t* fetch_running_task();

void task_term();

#endif
