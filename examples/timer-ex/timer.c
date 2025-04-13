#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>

void sig_handler(int signum)
{
    static int i = 0;
    if(signum == SIGALRM) {
        printf("seconds: %d\n", ++i);
    }
}
int main(void)
{
    struct itimerval timer;

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;

    signal(SIGALRM, sig_handler);

    if(setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("timer error");
        exit(EXIT_FAILURE);
    }

    while(true) {
        pause();
    }

    return 0;
}
