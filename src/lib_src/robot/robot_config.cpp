#include "lib_header/robot_h/robot_config.h"

// Alliance color 
bool isRed = false;

// Controller(s)
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drive Motors
pros::Motor leftFrontDrive(10, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftMidDrive(9, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);      
pros::Motor leftBackDrive(8, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);      
pros::Motor rightFrontDrive(20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightMidDrive(19, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);      
pros::Motor rightBackDrive(18, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);  

// Subsystem motors
pros::Motor leftCata(11, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightCata(1, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);

// Motor Groups
pros::Motor_Group leftDrive({leftFrontDrive, leftMidDrive, leftBackDrive});
pros::Motor_Group rightDrive({rightFrontDrive, rightMidDrive, rightBackDrive});
pros::Motor_Group cataMotors({leftCata, rightCata});

// Sensors
pros::Imu inertial(12);
pros::Rotation frontEnc(13, false);
pros::Rotation sideEnc(14, false);
pros::Rotation cataEnc(15, false);
pros::Optical optical(16, 20);

// Digital I/O
pros::ADIDigitalOut leftWing('A', false);
pros::ADIDigitalOut rightWing('B', false);
pros::ADIDigitalOut bandRelease('C', false);
