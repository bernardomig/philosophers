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
  int live_iteractions;
  { // Define live
    int max_live = sim->params->PHILOSOPHER_MIN_LIVE;
    int min_live = sim->params->PHILOSOPHER_MIN_LIVE;
    live_iteractions = random_range(min_live, max_live);
  }

  while(live_iteractions > 0){
    think(sim, p);
    choose_meal(sim, p);
    // get_food(sim, p);
    // get_cutlery(sim, p);
    eat(sim, p);
    // return_cutlery();
    --live_iteractions;
  }

  dead(sim, p);

}

void think(Simulation *sim,Philosopher *p){
  p->state = P_THINKING;
  logger(sim);
  random_sleep(sim->params->THINK_TIME);
  p->state = P_HUNGRY;
  logger(sim);
}

void choose_meal(Simulation *sim,Philosopher *p) {
  if(rand() % 100 < sim->params->CHOOSE_PIZZA_PROB)
    p->meal = P_GET_PIZZA;
  else
    p->meal = P_GET_SPAGHETTI;
  logger(sim);
}

void eat(Simulation *sim,Philosopher *p) {
  p->state = P_EATING;
  if(p->meal == P_GET_PIZZA) {
    p->meal = P_EAT_PIZZA;
  }
  else if(p->meal == P_GET_SPAGHETTI) {
    p->meal = P_GET_SPAGHETTI;
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