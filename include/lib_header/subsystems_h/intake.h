#ifndef INTAKE_H
#define INTAKE_H
#include "main.h"

// ******** Intake Constants ******** //

// ******** Intake Helper Functions ******** //
/**
 * @brief Spin intake at a specified voltage
 * @param intakeVolt Intake voltage from 127 to -127
*/
extern void setIntake(int intakeVolt);

/**
 * @brief Set intake brake mode
 * @param brakeMode Brake mode: HOLD, BRAKE, COAST
*/
extern void setIntakeBrakeMode(pros::motor_brake_mode_e brakeMode);

/**
 * @brief Stop intake with a specified brake mode
 * @param brakeMode Brake mode: HOLD, BRAKE, or COAST
*/
extern void stopIntake(pros::motor_brake_mode_e_t brakeMode);

// ******** Intake Opcontrol Function ******** //
extern void intakeOpControl();

#endif