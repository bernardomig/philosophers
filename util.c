#include "util.h"

int random_range(int min, int max)
{
    return min + (int)(rand() / ((double)RAND_MAX + 1) * (max - min + 1));
}

void random_sleep(int time)
{
    usleep(rand() % (time*1000));
}