/**
 * \brief Dining room
 *  
 * \author Miguel Oliveira e Silva - 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>
#include <string.h>
#include <locale.h>
#include "parameters.h"
#include "dining-room.h"
#include "waiter.h"
#include "logger.h"

bool getPizza(DiningRoom* dr)
{
    if(dr->pizza > 0) {
        --dr->pizza;
        return true;
    }
    else {
        return false;
    }
}
bool getSpaghetti(DiningRoom* dr)
{
    if(dr->spaghetti > 0) {
        --dr->spaghetti;
        return true;
    }
    else {
        return false;
    }
}

/* put your code here */
