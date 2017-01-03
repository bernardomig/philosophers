/**
 *  \brief Philosopher module
 *
 * \author Miguel Oliveira e Silva - 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "util.h"
#include "philosopher.h"
#include "dining-room.h"
#include "simulation.h"
#include "logger.h"

/* put your code here */

void philosopher(Simulation *sim, Philosopher *p) {
  p->state=P_BIRTH;
  srand((unsigned) getpid());
  int live_iteractions;
  { // Define live
    int max_live = sim->params->PHILOSOPHER_MIN_LIVE;
    int min_live = sim->params->PHILOSOPHER_MIN_LIVE;
    live_iteractions = random_range(min_live, max_live);
  }

  while(live_iteractions > 0){
    think(sim, p);
    choose_meal(sim, p);
    //get_cutlery(sim, p);
    eat(sim, p);
    //ret_cutlery(sim, p);
    --live_iteractions;
  }

  dead(sim, p);

}

void think(Simulation *sim,Philosopher *p) {
  p->state = P_THINKING;
  logger(sim);
  random_sleep(sim->params->THINK_TIME);
  p->state = P_HUNGRY;
  logger(sim);
}

void choose_meal(Simulation *sim,Philosopher *p) {
  if(rand() % 100 < sim->params->CHOOSE_PIZZA_PROB) {
    p->meal = P_GET_PIZZA;
    if(!getPizza(sim)) {
      waiterRequestPizza(sim);
      while(!getPizza(sim)) {
        usleep(100);
      }
    }
  }
  else {
    p->meal = P_GET_SPAGHETTI;
    if(!getSpaghetti(sim)) {
      waiterRequestSpaghetti(sim);
      while(!getSpaghetti(sim)) {
        usleep(100);
      }
    }
  }

  logger(sim);
}

void get_cutlery(Simulation* sim, Philosopher* p)
{
  p->cutlery[0] = P_GET_FORK;
  logger(sim);
  if(!getForks(sim)) {
    waiterRequestCutlery(sim);
    while(!getForks(sim));
  }
  p->cutlery[0] = P_FORK;
  logger(sim);

  if(p->meal == P_GET_PIZZA)
  {
    p->cutlery[1] = P_GET_KNIFE;
    logger(sim);
    if(!getKnives(sim)) {
      waiterRequestCutlery(sim);
      while(!getKnives(sim));
    }
    p->cutlery[1] = P_KNIFE;
    logger(sim);
  }
  else {
    p->cutlery[1] = P_GET_FORK;
    logger(sim);
    if(!getForks(sim)) {
      waiterRequestCutlery(sim);
      while(!getForks(sim));
    }
    p->cutlery[1] = P_FORK;
    logger(sim);
  }
}

void ret_cutlery(Simulation* sim, Philosopher* p)
{

  retForks(sim);
  p->cutlery[0] = P_PUT_FORK;
  logger(sim);
  if(p->cutlery[1] == P_KNIFE)
  {
    retKnives(sim);
    p->cutlery[1] = P_PUT_KNIFE;
    logger(sim);
  }
  else {
    retForks(sim);
    p->cutlery[1] = P_PUT_FORK;
    logger(sim);
  }
  p->cutlery[0] = P_NOTHING;
  p->cutlery[1] = P_NOTHING;
  logger(sim);
}

void eat(Simulation *sim,Philosopher *p) {
  p->state = P_EATING;
  if(p->meal == P_GET_PIZZA) {
    p->meal = P_EAT_PIZZA;
  }
  else if(p->meal == P_GET_SPAGHETTI) {
    p->meal = P_EAT_SPAGHETTI;
  }
  logger(sim);
  random_sleep(sim->params->EAT_TIME);
  p->state = P_FULL;
  p->meal = P_NONE;
  logger(sim);
}

void dead(Simulation *sim,Philosopher *p) {
  p->state = P_DEAD;
  logger(sim);
}