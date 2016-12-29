#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <unistd.h>


int random_range(int min, int max);

void random_sleep(int time);

void* mem_alloc(int size);

#endif