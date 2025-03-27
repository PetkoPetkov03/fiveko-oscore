#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../libs/task/task.h"
#include "../../libs/queue/que.h"

void func1(void);
void func2(void);
void func3(void);

int main(void)
{
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

    task_flush();

    return 0;
}

void func1(void)
{
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
