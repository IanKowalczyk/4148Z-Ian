#ifndef MOTION_FUNCTIONS_H
#define MOTION_FUNCTIONS_H
#include "main.h"
#include <vector>

// namespace AUTO {}

// enum class auto_movement_flag {NONE, FULL, REV} currentMovementFlag;

// ******** Universal Variables ******** //
extern bool driveSettled;
extern bool full_power;
extern int max_time;

// ******** Movement Task ******** //
extern void autoMovementTask();

// ******** Wait Functions ******** //
/**
 * @brief Delay until movement is finished and drive is settled
 * @param msecDelay Addition delay after the drive is settled 
*/
extern void waitUntilSettled(int msecDelay);
/**
 * @brief Delay until robot is near target distance or pose
 * @param threshold Error threshold for robot to be considered near target
 * @param msecDelay Addition delay after robot is near target 
*/
extern void waitUntilNear(double threshold, int msecDelay);

/**
 * @brief Forces the drive to stop and switch autoMovementState to OFF; used for when running at full power
 * @param mode Brake mode to stop drive in
*/
extern void forceStopDrive(pros::motor_brake_mode_e mode);


#endif