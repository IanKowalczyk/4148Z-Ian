#ifndef CURVE_H
#define CURVE_H
#include "main.h"
#include "lib_header/api/robot_api.h"
#include "lib_header/motion_h/move.h"


// ******** Variables ******** //


// ******** Function ******** //
extern void curve();


// ******** Setters ******** //
/**
 * @brief Setter for curve function
 * @param distance Distance to move after finishing arc
 * @param endAngle End angle for arc; robot will turn left if negative and turn right if positive
 * @param radius Radius of the arc the robot will travel
 * @param maxDrivePower Max power for drive
 * @param maxTurnPower Max power for turn
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
*/
extern void setCurve(double distance, double endAngle, double radius, int maxDrivePower, int maxTurnPower, int maxTime);


// ******** Chained Setters ******** //


#endif