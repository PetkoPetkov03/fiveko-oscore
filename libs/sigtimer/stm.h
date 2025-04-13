#ifndef __OS_SIGTIMER__
#define __OS_SIGTIMER__
#include <sys/time.h>

struct itimeval {
    struct timeval it_iterval;
    struct timeval it_value;
};

struct timeval init_timev(time_t tv_sec, suseconds_t tv_usec);

struct itimeval init_itimev(
struct timeval it_iterval,
struct timeval it_value
);
#endif
