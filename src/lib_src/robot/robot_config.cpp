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
pros::Motor leftCata(11, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);  // 11 W
pros::Motor rightCata(1, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_COUNTS);   // 5.5 W
pros::Motor intake(6, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_COUNTS);     // 5.5 W

// Motor Groups
pros::Motor_Group leftDrive({leftFrontDrive, leftMidDrive, leftBackDrive});
pros::Motor_Group rightDrive({rightFrontDrive, rightMidDrive, rightBackDrive});
pros::Motor_Group cataMotors({leftCata, rightCata});

// Sensors
pros::Imu inertial(21);
pros::Rotation frontEnc(7, true);   // reversed
pros::Rotation sideEnc(12, true);   // reversed
pros::Rotation cataEnc(2, false);
pros::Optical optical(17, 40);

// Digital I/O
pros::ADIDigitalOut leftWing('A', false);
pros::ADIDigitalOut rightWing('B', false);
pros::ADIDigitalOut climb('C', false);
// pros::ADIDigitalOut bandRelease('C', false);
