#ifndef CATA_H
#define CATA_H
#include "main.h"
#include <string>

// Contstants
extern int SHORT_PULLBACK_TICKS;
extern int FULL_PULLBACK_TICKS;
extern int PULLBACK_TIMEOUT;
extern int PULLBACK_THRESHOLD;

// Variables
extern int pullbackCount;

// Matchload variables
extern bool matchloadState;
extern int fireCount;
extern int fireTarget;


// Helper functions
extern void setCata(int volt);
extern void setCataBrakeMode(pros::motor_brake_mode_e brakeMode);
extern void stopCata(pros::motor_brake_mode_e brakeMod);

// Cata  
extern void fire(int numTimes, int newPullback);
extern void setMatchload(int numTimes, bool waitForCompletion);
extern void shooterTask();

// Opcontrol function
extern void cataOpControl();
extern void matchloadOpControl();

#endif