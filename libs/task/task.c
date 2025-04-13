#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include "../queue/que.h"

#define FIBERSTACK 1024*64

static queue* tcb_queue;
static task_t* running_task;
static ucontext_t main_context;

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

task_t* fetch_running_task() {
    return unwrap_node(front(tcb_queue));
}

void task_term(task_t* term_task) {
    free(term_task->context.uc_stack.ss_sp);
    free(term_task);
}

int task_exec() {
    if(running_task == NULL) {
        running_task = unwrap_node(front(tcb_queue));
    }

    if(running_task == NULL || running_task->func == NULL) {
        return -1;
    }

    running_task->func();

    return 0;
}

int switch_task() {
    ucontext_t prev_context;
    if(!running_task) {
        running_task = fetch_running_task();
    }else{
        printf("swap pop: %p\n", running_task);
        prev_context = running_task->context;
        pop(tcb_queue);
        push(tcb_queue, running_task);

        running_task = unwrap_node(front(tcb_queue));
    }

    swapcontext(&prev_context, &(running_task->context));
    printf("swap push: %p\n", running_task);

    if(running_task == NULL) {
        perror("task queue depleted unexpectidly");
        return -1;
    }

    return 0;
}

int test_tasks(void)
{
    // printf("task front: %d, %p, %p\n",
    // node_gid(front(tcb_queue)), front(tcb_queue),
    // unwrap_node(front(tcb_queue)));

    // printf("task rear: %d, %p, %p\n",
    // node_gid(rear(tcb_queue)), rear(tcb_queue),
    // unwrap_node(rear(tcb_queue)));

    // pop(tcb_queue);

    // printf("task front: %d, %p, %p\n",
    // node_gid(front(tcb_queue)), front(tcb_queue),
    // (task_t*)unwrap_node(front(tcb_queue)));

    task_t* task_a = unwrap_node(front(tcb_queue));
    pop(tcb_queue);
    task_t* task_b = unwrap_node(front(tcb_queue));
    pop(tcb_queue);
    task_t* task_c = unwrap_node(front(tcb_queue));
    pop(tcb_queue);

    task_a->func();
    task_b->func();
    task_c->func();

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
