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
    bool ret;
    lock(SEMPH_PIZZAS);
    if(sim->diningRoom->pizza > 0) {
        --sim->diningRoom->pizza;
        ret = true;
    }
    else {
        ret = false;
    }
    unlock(SEMPH_PIZZAS);
    return ret;
}
bool getSpaghetti(Simulation* sim)
{
    bool ret;
    lock(SEMPH_SPAGHETTI);
    if(sim->diningRoom->spaghetti > 0) {
        --sim->diningRoom->spaghetti;
        ret = true;
    }
    else {
        ret = false;
    }
    unlock(SEMPH_SPAGHETTI);
    return ret;
}

bool getForks(Simulation* sim)
{
    bool ret;
    lock(SEMPH_CUTLERY);
    if(sim->diningRoom->cleanForks > 0) {
        --sim->diningRoom->cleanForks;
        ret = true;
    }
    else
        ret = false;
    unlock(SEMPH_CUTLERY);
    return ret;
}

bool getForkAndFork(Simulation* sim)
{
    bool ret;
    lock(SEMPH_CUTLERY);
    if(sim->diningRoom->cleanForks >= 2) {
        sim->diningRoom->cleanForks -= 2;
        ret = true;
    }
    else
        ret = false;
    unlock(SEMPH_CUTLERY);
    return ret;
}

bool getForkAndKnife(Simulation* sim)
{
    bool ret;
    lock(SEMPH_CUTLERY);
    if(sim->diningRoom->cleanForks > 0 && sim->diningRoom->cleanKnives > 0) {
        --sim->diningRoom->cleanForks;
        --sim->diningRoom->cleanKnives;
        ret = true;
    }
    else
        ret = false;
    unlock(SEMPH_CUTLERY);
    return ret;
}

void retForks(Simulation* sim)
{
    lock(SEMPH_CUTLERY);
    ++sim->diningRoom->dirtyForks;
    unlock(SEMPH_CUTLERY);
}

bool getKnives(Simulation* sim)
{
    bool ret;
    lock(SEMPH_CUTLERY);
    if(sim->diningRoom->cleanKnives > 0) {
        --sim->diningRoom->cleanKnives;
        ret = true;
    }
    else
        ret = false;
    unlock(SEMPH_CUTLERY);
    return ret;
}

void retKnives(Simulation* sim)
{
    lock(SEMPH_CUTLERY);
    ++sim->diningRoom->dirtyKnives;
    unlock(SEMPH_CUTLERY);
}