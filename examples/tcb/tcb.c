#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../libs/task/task.h"
#include "../../libs/queue/que.h"
#include "../../libs/dispatcher/fdispatch.h"

void func1(void);
void func2(void);
void func3(void);

int main(void)
{
    t_dispatcher* dispatcher = init_dispatcher(1, 0);

    if(dispatcher == NULL) {
        perror("dispatcher error");
        exit(EXIT_FAILURE);
    }

    if(create_task(&func1) == -1) {
        perror("task fail");
        exit(EXIT_FAILURE);
    }

    if(create_task(&func2) == -1) {
        perror("task fail");
        exit(EXIT_FAILURE);
    }

    if(create_task(&func3) == -1) {
        perror("task fail");
        exit(EXIT_FAILURE);
    }

    dispatch();

    task_flush();

    return 0;
}

void func1(void)
{
    //printf("+\n");
    while(true)
    {
        printf("+\n");
    }
}

void func2(void)
{
    while(true)
    {
        printf("-\n");
    }
}

void func3(void)
{
    while(true)
    {
        printf("!\n");
    }
}
