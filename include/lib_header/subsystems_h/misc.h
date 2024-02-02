#ifndef MISC_H
#define MISC_H
#include "main.h"

// Variables
extern bool brakeReady;

// Wing Opcontrol 
extern void wingOpControl(pros::controller_digital_e_t wingButton);

// Brake Opcontrol
extern void brakeOpControl();

// Climb Opcontrol
extern void climbOpControl();
extern void climbUp();
extern void climbDown();

#endif