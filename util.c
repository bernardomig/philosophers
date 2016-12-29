#include "util.h"

#include <stdio.h>

int random_range(int min, int max)
{
    return min + (int)(rand() / ((double)RAND_MAX + 1) * (max - min + 1));
}

void random_sleep(int time)
{
    usleep(rand() % (time*1000));
}

/**
 * Memory error is not recoverable.
 */
void* mem_alloc(int size)
{
   void* result = malloc(size);
   if (result == NULL)
   {
      fprintf(stderr, "ERROR: no memory!\n");
      exit(EXIT_FAILURE);
   }
   return result;
}

