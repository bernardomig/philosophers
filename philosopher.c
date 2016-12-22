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
#include "philosopher.h"
#include "dining-room.h"
#include "simulation.h"
#include "logger.h"

/* put your code here */

void philosopher(Simulation *sim, Philosopher *p){
  Philosopher *p;
  p->state=P_BIRTH;


  while(1){
    think(sim,p);  //fica a dormir até lhe dar a fome
    choose_meal();
    eat();

    //take_cutlery(i);
    //put_dirty_cutlery(i);
  }

}

void think(Simulation *sim,Philosopher *p){
  p->state = P_THINKING;
  logger(sim);
  usleep((random() % sim->params->THINK_TIME)*1000); //sleeping for [0,THINK_TIME] ms
}

void choose_meal(){
  //choose a meal
  //if(random() < sim->params->CHOOSE_PIZZA_PROB * ((double)RAND_MAX + 1.0))
  if(randomBoolean(sim->params->CHOOSE_PIZZA_PROB)
    p->meal = P_GET_PIZZA;
  else
    p->meal = P_GET_SPAGHETTI;
}

void randomSleep(int min, int max){ //microseconds
  min=min*1000; //passing from milliseconds to microseconds
  max=max*1000;
  //usleep(min + (int)((double)random()/(double)RAND_MAX)*(max-min));
  usleep(min + (int) (rand() / ((double)RAND_MAX + 1) * (max - min + 1)));
}

int randomBoolean(double boolProb){
  return ((double)random()/(double)RAND_MAX) < boolProb;
}

/*
void take_cutlery(int i){

    sem_wait(&mutex);  //Enter critical region
    //ver se existem facas ou garfos lavados suficientes para comer, se não houver mandar request ao empregado


    sem_post(&mutex); //Leave critical region
}
*/
