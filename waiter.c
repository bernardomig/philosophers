/**
 *  \brief Waiter module
 *  
 * \author Miguel Oliveira e Silva - 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "dining-room.h"
#include "logger.h"

/* put your code here */

void waiterLoop(Simulation* sim)
{
    bool stillRunning = false;
    int i;
    for(i = 0; i < sim->params->NUM_PHILOSOPHERS; i++) {
        if(sim->philosophers[i]->state != P_DEAD) {
            stillRunning = true;
            break;
        }
    }
    if(!stillRunning) {
        waiterWashCutlery(sim);
        sim->waiter->state = W_DEAD;
        logger(sim);
        exit(0);
    }

    if(sim->waiter->reqCutlery == W_ACTIVE) {
        waiterWashCutlery(sim);
    }
    else if(sim->waiter->reqPizza == W_ACTIVE) {
        waiterReplenishPizza(sim);
    }
    else if(sim->waiter->reqSpaghetti == W_ACTIVE) {
        waiterReplenishSpaghetti(sim);
    }
        
}

void waiterReplenishPizza(Simulation* sim)
{
    sim->waiter->state = W_REQUEST_PIZZA;
    logger(sim);
    lock(SEMPH_PIZZAS);
    sim->diningRoom->pizza = sim->params->NUM_PIZZA;
    unlock(SEMPH_PIZZAS);
    sim->waiter->reqPizza = W_INACTIVE;
    sim->waiter->state = W_SLEEP;
    logger(sim);
}

void waiterReplenishSpaghetti(Simulation* sim)
{
    sim->waiter->state = W_REQUEST_SPAGHETTI;
    logger(sim);
    lock(SEMPH_SPAGHETTI);
    sim->diningRoom->spaghetti = sim->params->NUM_SPAGHETTI;
    unlock(SEMPH_SPAGHETTI);
    sim->waiter->reqSpaghetti = W_INACTIVE;
    sim->waiter->state = W_SLEEP;
    logger(sim);
}

void waiterWashCutlery(Simulation* sim)
{
    lock(SEMPH_CUTLERY);
    bool no_cutlery = sim->diningRoom->dirtyForks == 0 && sim->diningRoom->dirtyKnives == 0;
    unlock(SEMPH_CUTLERY);
    if(no_cutlery) {
        sim->waiter->reqCutlery = W_INACTIVE;
        return;
    }

    sim->waiter->state = W_REQUEST_CUTLERY;
    logger(sim);
    lock(SEMPH_CUTLERY);
    sim->diningRoom->dirtyForksInWaiter = sim->diningRoom->dirtyForks;
    sim->diningRoom->dirtyForks = 0;
    sim->diningRoom->dirtyKnivesInWaiter = sim->diningRoom->dirtyKnives;
    sim->diningRoom->dirtyKnives = 0;
    unlock(SEMPH_CUTLERY);
    logger(sim);
    random_sleep(sim->params->WASH_TIME);
    lock(SEMPH_CUTLERY);
    sim->diningRoom->cleanKnives += sim->diningRoom->dirtyKnivesInWaiter;
    sim->diningRoom->cleanForks += sim->diningRoom->dirtyForksInWaiter;
    sim->diningRoom->dirtyForksInWaiter = 0;
    sim->diningRoom->dirtyKnivesInWaiter = 0;
    unlock(SEMPH_CUTLERY);
    sim->waiter->state = W_SLEEP;
    sim->waiter->reqCutlery = W_INACTIVE;
    logger(sim);
}

void waiterRequestPizza(Simulation* sim)
{
    sim->waiter->reqPizza = W_ACTIVE;
}

void waiterRequestSpaghetti(Simulation* sim)
{
    sim->waiter->reqSpaghetti = W_ACTIVE;
}

void waiterRequestCutlery(Simulation* sim)
{
    sim->waiter->reqCutlery = W_ACTIVE;
}