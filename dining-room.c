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

bool getPizza(Simulation* sim)
{
    if(sim->diningRoom->pizza > 0) {
        --sim->diningRoom->pizza;
        return true;
    }
    else {
        return false;
    }
}
bool getSpaghetti(Simulation* sim)
{
    if(sim->diningRoom->spaghetti > 0) {
        --sim->diningRoom->spaghetti;
        return true;
    }
    else {
        return false;
    }
}

bool getForks(Simulation* sim)
{
    if(sim->diningRoom->cleanForks > 0) {
        --sim->diningRoom->cleanForks;
        return true;
    }
    else
        return false;
}

void retForks(Simulation* sim)
{
    ++sim->diningRoom->dirtyForks;
}

bool getKnives(Simulation* sim)
{
    if(sim->diningRoom->cleanKnives > 0) {
        --sim->diningRoom->cleanKnives;
        return true;
    }
    else
        return false;
}

void retKnives(Simulation* sim)
{
    ++sim->diningRoom->dirtyKnives;
}