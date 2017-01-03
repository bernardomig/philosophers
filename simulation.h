/**
 * \brief Simulation data structure
 *  
 * \author Miguel Oliveira e Silva - 2016
 */

#ifndef SIMULATION_H
#define SIMULATION_H

struct _Waiter_;
struct _Parameters_;
struct _DiningRoom_;
struct _Philosopher_;

typedef struct _Simulation_ {
   struct _Parameters_* params;
   struct _DiningRoom_* diningRoom;
   struct _Philosopher_** philosophers;
   struct _Waiter_* waiter;
} Simulation;

#include "util.h"
#include "parameters.h"
#include "dining-room.h"
#include "philosopher.h"
#include "waiter.h"

#include <stdbool.h>

Simulation* initSimulation(Simulation* sim, Parameters* params);

typedef
enum _SemphType_
{
    SEMPH_PHILOSOPHERS = 0b0001,
    SEMPH_PIZZAS       = 0b0010,
    SEMPH_SPAGHETTI    = 0b0100,
    SEMPH_CUTLERY      = 0b1000,
    SEMPH_FOOD         = 0b0110,
    SEMPH_ALL          = 0b1111
}
SemphType;

void lock(SemphType);
void unlock(SemphType);

#endif
