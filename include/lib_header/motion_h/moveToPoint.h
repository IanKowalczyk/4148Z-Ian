#ifndef MOVE_TO_POINT_H
#define MOVE_TO_POINT_H
#include "main.h"
#include "lib_header/api/robot_api.h"
#include "lib_header/subsystems_h/drive.h"
#include "lib_header/motion_h/motionFunctions.h"
#include "lib_header/api/control_api.h"


// ******** Variables ******** //
extern double translation_error;
extern double target_x;
extern double target_y;
extern double end_orientation;
extern int max_translate_power;
extern int max_rotate_power;
extern int max_orient_power;
extern bool movement_reversed;


// ******** Function ******** //
extern void moveToPoint();


// ******** Setters ******** //
/**
 * @brief Full setter for the moveToPoint function
 * @param targetX Target x coordinate, in inches @param targetY Target y coordinate, in inches
 * @param endOrientation End angle after arriving at point
 * @param maxTranslatePower Max power for driving to target @param maxRotatePower Max power for turn to target
 * @param maxOrientPower Max power for end orientation turn
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param reversed If true, reverse movement. False (forward) by default
*/
extern void setMoveToPoint(double targetX, double targetY, double endOrientation, int maxTranslatePower, 
        int maxRotatePower, int maxOrientPower, int maxTime, bool reversed);
        
/**
 * @brief Wrapped setter for the moveToPoint function: No end orientation
 * @param targetX Target x coordinate, in inches @param targetY Target y coordinate, in inches
 * @param maxTranslatePower Max power for driving to target @param maxRotatePower Max power for turn to target
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param reversed If true, reverse movement. False (forward) by default
*/
extern void setMoveToPoint(double targetX, double targetY, int maxTranslatePower, int maxRotatePower,  int maxTime, bool reversed);

/**
 * @brief Wrapped setter for the moveToPoint function: Only target x, y and timeout
 * @param targetX Target x coordinate, in inches @param targetY Target y coordinate, in inches
 * @param maxTime Maximum time the function is allowed to run for; default 2000 ms
 * @param reversed If true, reverse movement. False (forward) by default
*/
extern void setMoveToPoint(double targetX, double targetY, int maxTime, bool reversed);


// ******** Chained Setters ******** //
extern void chainMoveToPoint(std::vector<double> pose1, std::vector<double> power1, int maxTime1, 
                        std::vector<double> pose2, std::vector<double> power2, int maxTime2, double threshold);

extern void extendMoveToPoint(double targetX, double targetY, int maxTranslatePower, int maxRotatePower, int maxTime, bool reversed);

#endif