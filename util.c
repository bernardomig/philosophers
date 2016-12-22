#include "util.h"

int random_range(int min, int max)
{
    return rand() % (max - min) + min;
}

void random_sleep(int time)
{
    usleep(rand() % (time*1000));
}