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
        sim->waiter->state = W_DEAD;
        logger(sim);
        exit(0);
    }

    if(sim->waiter->reqCutlery == W_ACTIVE) {

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
    sim->diningRoom->pizza = sim->params->NUM_PIZZA;
    sim->waiter->reqPizza = W_INACTIVE;
    sim->waiter->state = W_SLEEP;
    logger(sim);
}

void waiterReplenishSpaghetti(Simulation* sim)
{
    sim->waiter->state = W_REQUEST_SPAGHETTI;
    logger(sim);
    sim->diningRoom->spaghetti = sim->params->NUM_SPAGHETTI;
    sim->waiter->reqSpaghetti = W_INACTIVE;
    sim->waiter->state = W_SLEEP;
    logger(sim);
}

void waiterReplenishCutlery(Simulation* sim)
{

}

void waiterRequestPizza(Simulation* sim)
{
    sim->waiter->reqPizza = W_ACTIVE;
    logger(sim);
}

void waiterRequestSpaghetti(Simulation* sim)
{
    sim->waiter->reqSpaghetti = W_ACTIVE;
    logger(sim);
}
