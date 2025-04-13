#ifndef __OS_DISPATCH__
#define __OS_DISPATCH__
#include <sys/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

typedef struct itimerval t_timer;

typedef struct __t_dispatcher__ {
    t_timer timer;
    struct sigaction saction;
} t_dispatcher;

t_dispatcher* init_dispatcher(time_t seconds, suseconds_t micseconds);

void _dispatch_handler(int signal);

void dispatch();

#endif
