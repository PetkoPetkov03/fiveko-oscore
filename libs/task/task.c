#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include "../queue/que.h"

#define FIBERSTACK 1024*64

static queue* tcb_queue;

int create_task(void (*start_routine)())
{
    if(!tcb_queue) {
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

    free(task->context.uc_stack.ss_sp);
    free(task);

    return 0;
}

int test_tasks(void)
{
    printf("task front: %d, %p\n",
    tcb_queue->front->id, tcb_queue->front->content);

    printf("task rear: %d, %p\n",
    tcb_queue->rear->id, tcb_queue->rear->content);

    printf("content: %p\n", pop(tcb_queue));

    printf("task front: %d, %p\n",
    tcb_queue->front->id, tcb_queue->front->content);
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
