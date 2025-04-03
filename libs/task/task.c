#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include "../queue/que.h"

#define FIBERSTACK 1024*64

static queue* tcb_queue;

int create_task(void (*start_routine)())
{
    if(tcb_queue == NULL) {
        tcb_queue = queue_init();
    }

    printf("task\n");
    task_t* task = (task_t*)malloc(sizeof(task_t));
    printf("task end\n");

    if(!task) {
        return -1;
    }

    task->func = start_routine;

    getcontext(&(task->context));

    task->context.uc_link = NULL;
    task->context.uc_stack.ss_sp = malloc(FIBERSTACK);
    task->context.uc_stack.ss_size = FIBERSTACK;
    task->context.uc_stack.ss_flags = 0;

    printf("context start\n");
    makecontext(&(task->context), task->func, 0);
    printf("context end\n");

    printf("push start\n");
    push(tcb_queue, task);
    printf("push end\n");

    return 0;
}

int test_tasks(void)
{
    printf("task front: %d, %p, %p\n",
    node_gid(front(tcb_queue)), front(tcb_queue),
    unwrap_node(front(tcb_queue)));

    printf("task rear: %d, %p, %p\n",
    node_gid(rear(tcb_queue)), rear(tcb_queue),
    unwrap_node(rear(tcb_queue)));

    pop(tcb_queue);

    printf("task front: %d, %p, %p\n",
    node_gid(front(tcb_queue)), front(tcb_queue),
    (task_t*)unwrap_node(front(tcb_queue)));


    return 0;
}

int task_flush(void)
{
    queue_destroy(&tcb_queue);

    if(tcb_queue != NULL) {
        return 1;
    }

    return 0;
}
