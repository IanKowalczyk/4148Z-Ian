#ifndef DRIVE_H
#define DRIVE_H
#include "main.h"

// ******** Drive Constants ******** //
extern double TURN_SENS;
extern double DRIVE_BRAKE_THRESHOLD;

// ******** Drive Helper Functions ******** //
/**
 * @brief Set left / right drive to a specified voltage
 * @param leftVolt Voltage for leftDrive: -127 to 127
 * @param rightVolt Voltagfe for rightDrive: -127 to 127
*/
extern void setDrive(int leftVolt, int rightVolt);

/**
 * @brief Set drive brake mode
 * @param brakeMode Brake mode: HOLD, BRAKE, COAST
*/
extern void setDriveBrakeMode(pros::motor_brake_mode_e brakeMode);

/**
 * @brief Stop drive with a specified brake mode
 * @param brakeMode Brake mode: HOLD, BRAKE, or COAST
*/
extern void stopDrive(pros::motor_brake_mode_e brakeMode);

// ******** Drive Opcontrol functions  ******** //
extern void splitArcade(pros::motor_brake_mode_e driveBrakeMode);
extern void curveSplitArcade();
extern void drivePtoOpControl();

#endif