#ifndef MOVE_H
#define MOVE_H
#include "main.h"
#include "lib_header/api/robot_api.h"
#include "lib_header/subsystems_h/drive.h"
#include "lib_header/motion_h/motionFunctions.h"
#include "lib_header/api/control_api.h"

// ******** Variables ******** //
extern double drive_position;
extern double drive_error;
extern double drive_target;
extern double turn_target;
extern int max_drive_power;
extern int max_turn_power;
extern bool drive_slew;
extern bool turn_slew;


// ******** Function ******** //
extern void move();


// ******** Setters ******** //
/**
 * @brief Full setter for the move function: Set drive only, turn only, or both simultaneously 
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxDrivePower Max power for drive @param maxTurnPower Max power for turn 
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param fullPower If true, drive at full power instead of using PID 
 * @param driveSlew Boolean for using slew rate for drive @param turnSlew Boolean for using slew rate for turn
*/
extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime, bool fullPower, bool driveSlew, bool turnSlew);

/**
 * @brief Wrapped setter for the move function: Use full power
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxDrivePower Max power for drive @param maxTurnPower Max power for turn 
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param fullPower If true, drive at full power instead of using PID
*/
extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime, bool fullPower);

/**
 * @brief Wrapped setter for the move function: No slew rate
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxDrivePower Max power for drive @param maxTurnPower Max power for turn 
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
*/
extern void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime);

/**
 * @brief Wrapped setter for the move function: Only drive / turn target and timeout
 * @param driveTarget Target position for the drive, in inches  @param turnTarget Target heading for drive
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
*/
extern void setMove(double driveTarget, double turnTarget, int maxTime);


// ******** Chained Setters ******** //
extern void chainMove(std::vector<double> target1, std::vector<double> power1, int maxTime1, 
                std::vector<double> target2, std::vector<double> power2, int maxTime2, double threshold);
extern void extendMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime);

#endif