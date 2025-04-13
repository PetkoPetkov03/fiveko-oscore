#include "./fdispatch.h"
#include "../task/task.h"

t_dispatcher* init_dispatcher(time_t seconds, suseconds_t micseconds)
{
    t_dispatcher* dispatcher = (t_dispatcher*)malloc(sizeof(t_dispatcher));

    struct timeval it_interval;
    struct timeval it_value;

    it_interval.tv_sec = seconds;
    it_interval.tv_usec = micseconds;

    it_value.tv_sec = seconds;
    it_value.tv_usec = micseconds;

    dispatcher->timer.it_interval = it_interval;
    dispatcher->timer.it_value = it_value;

    dispatcher->saction.sa_handler = &_dispatch_handler;
    dispatcher->saction.sa_flags = SA_NODEFER;

    if(setitimer(ITIMER_REAL, &(dispatcher->timer), NULL) == -1) {
        perror("timer error");

        return NULL;
    }

    sigaction(SIGALRM, &(dispatcher->saction), NULL);

    return dispatcher;
}

void _dispatch_handler(int sigaction)
{
    if(sigaction == SIGALRM) {
        switch_task();
    }
}

void dispatch() {
    while(true) pause();
}
