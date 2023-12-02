#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H
#include "main.h"

// Alliance color
extern bool isRed;

// Controller(s)
extern pros::Controller controller;

// Drive Motors
extern pros::Motor leftFrontDrive;
extern pros::Motor leftMidDrive;
extern pros::Motor leftBackDrive;
extern pros::Motor rightFrontDrive;
extern pros::Motor rightMidDrive;
extern pros::Motor rightBackDrive;

// Subsystem motors
extern pros::Motor leftCata;
extern pros::Motor rightCata;

// Motor Groups
extern pros::Motor_Group leftDrive;
extern pros::Motor_Group rightDrive;
extern pros::Motor_Group cataMotors;

// Sensors
extern pros::Imu inertial;
extern pros::Rotation frontEnc;
extern pros::Rotation sideEnc;
extern pros::Rotation cataEnc;
extern pros::Optical optical;

// Digital I/O
extern pros::ADIDigitalOut leftWing;
extern pros::ADIDigitalOut rightWing;
extern pros::ADIDigitalOut bandRelease;



#endif