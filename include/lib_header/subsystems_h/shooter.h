#ifndef SHOOTER_H
#define SHOOTER_H
#include "main.h"
#include <string>

// Contstants
extern int SHORT_PULLBACK_TICKS;
extern int FULL_PULLBACK_TICKS;
extern int MIN_FIRE_TIME;
extern int PULLBACK_TIMEOUT;
extern int PULLBACK_THRESHOLD;

// Variables
extern int pullbackCount;

// Matchload variables
extern bool matchloadState;
extern int triballsFired;
extern int triballFireTarget;


// Helper functions
extern void setShooter(int volt);
extern void setShooterBrakeMode(pros::motor_brake_mode_e brakeMode);
extern void stopShooter(pros::motor_brake_mode_e brakeMod);

// Shooter  
extern void fire(int numTimes, int newPullback);
extern void setMatchload(int numTimes, bool waitForCompletion);
extern void shooterTask();

// Opcontrol function
extern void shooterOpControl();
extern void matchloadOpControl();

#endif