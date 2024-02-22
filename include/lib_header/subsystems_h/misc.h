#ifndef MISC_H
#define MISC_H
#include "main.h"

// Variables
extern bool brakeReady;

// Wing Opcontrol 
extern void wingOpControl(pros::controller_digital_e_t wingButton);

// Brake Opcontrol
extern void brakeOpControl(pros::controller_digital_e_t brakeButton);

// Climb Opcontrol
extern void climbOpControl(pros::controller_digital_e_t b1, pros::controller_digital_e_t b2, pros::controller_digital_e_t b3);

// Climb functions
extern void climbUp();
extern void climbDown();

#endif