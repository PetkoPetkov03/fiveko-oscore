#include "stm.h"

struct timeval init_timev(time_t tv_sec, suseconds_t tv_usec)
{
    struct timeval val;

    val.tv_sec = tv_sec;
    val.tv_usec = tv_usec;

    return val;
}

struct itimeval init_itimev(struct timeval it_iterval, struct timeval it_value)
{
    struct itimeval val;

    val.it_iterval = it_iterval;
    val.it_value = it_value;

    return val;
}
