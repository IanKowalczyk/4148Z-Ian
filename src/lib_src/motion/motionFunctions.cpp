#include "lib_header/motion_h/motionFunctions.h"
// #include <cmath>
// #include <vector>

// TO DO
// Implement acceleration cap / maybe deaccel
// Boomerange alg
// synchronize tasks using pros::Task::delay_until for consistent loop execution
// Make curve function async
// Path following alg 

// **** kinematics tings **** //
// NO SLEW: travels 24in in 605 ms: 39.67 in/s
// SLEW:    travels 24in in 
	// tuning pid
	// setMove(24, 0, 120, 0, 2000, false, false, false);   // 605 ms
	// setMove(24, 0, 120, 0, 2000, false, true, false);    // 638 ms
	// setMove(0, 180, 0, 100, 1000);       // ~ 700 ms sometimes, 1000 ms sometimes else????
	// setMove(0, 90, 0, 100, 1000);        // 500 ms
	// setMoveToPoint(0, 24, 1000, false);  // 750 ms

// ********* RECOMMMENT LATER ********* //
// double IDEAL_DRIVE_VELOCITY = 39.67; // Inches per second
// double IDEAL_TURN_VELOCITY = 180;    // Degrees per second


// **************** Movement Variables **************** //

// Universal variables 
bool driveSettled = true; // false?
bool nearTarget = false;
bool full_power = false;
int max_time = 2000;


// **************** Auto Movement Task **************** //

void autoMovementTask() {
    // states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
    while(true) {
        // if(states.driveAutoStateIs(stateMachine::drive_auto_state::OFF)) {
        //     // pros::delay(5);
        //     // while(!states.driveAutoStateChanged) {pros::delay(5);}
        // }
        // else 
        if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE)) {
            move();
        }
        else if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE_TO_POINT)) {
            moveToPoint();
            // pros::screen::set_eraser(COLOR_BLACK);
            // pros::screen::erase();
            // pros::screen::set_pen(COLOR_YELLOW);
            // pros::screen::fill_rect(20, 20, 400, 400);
            // pros::delay(20);
        }
        pros::delay(10); // used to be 5ms
    }
}


// **************** Wait Functions **************** //

void waitUntilSettled(int msecDelay) {
    pros::delay(400);
    while(!driveSettled) {
        pros::delay(5);
        // debug box
        // pros::screen::set_eraser(COLOR_BLACK);
        // pros::screen::erase();
        // pros::screen::set_pen(COLOR_BLUE);
        // pros::screen::fill_rect(20, 20, 400, 400);
    }
    // driveSettled = false;
        
        // debug
        // pros::screen::set_eraser(COLOR_BLACK);
        // pros::screen::erase();

    // disable auto movement
    states.setDriveAutoState(stateMachine::drive_auto_state::OFF);

    // reset targets
    drive_target = turn_target = 0;
    target_x = target_x = end_orientation = 0;

    // delay
    pros::delay(msecDelay);
}

void waitUntilNear(double threshold, int msecDelay) {
    int functionTime = pros::c::millis();
    pros::delay(400); // minimum move time
    if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE)) {
        while(std::fabs(drive_error) > threshold && !driveSettled) {pros::delay(5);}
    }
    else if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE_TO_POINT)){ 
        while(std::fabs(translation_error) > threshold && !driveSettled) {pros::delay(5);}
    }
    
    pros::delay(msecDelay);
}

void forceStopDrive(pros::motor_brake_mode_e mode) {
    driveSettled = true;
    states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
    stopDrive(mode);
}