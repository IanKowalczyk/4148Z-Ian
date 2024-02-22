#include "lib_header/robot_h/robot_config.h"

// Alliance color 
bool isRed = false;

// Controller(s)
pros::Controller controller(pros::E_CONTROLLER_MASTER);
  
// Drive Motors
pros::Motor leftFrontDrive(7, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftMidDrive(2, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);      
pros::Motor leftBackDrive(12, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS);      
pros::Motor rightFrontDrive(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightMidDrive(10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);      
pros::Motor rightBackDrive(16, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS);  

// Subsystem motors
pros::Motor leftShooter(15, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);  // 11 W 
pros::Motor rightShooter(20, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_COUNTS);   // 5.5 W
pros::Motor intake(3, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_COUNTS);     // 5.5 W // 6

// Motor Groups
pros::Motor_Group leftDrive({leftFrontDrive, leftMidDrive, leftBackDrive});
pros::Motor_Group rightDrive({rightFrontDrive, rightMidDrive, rightBackDrive});
pros::Motor_Group shooterMotors({leftShooter, rightShooter});

// Sensors
pros::Imu inertial(5); // old = 18
pros::Rotation frontEnc(4, false);  // not reversed
pros::Rotation sideEnc(14, false);   // not reversed
pros::Rotation shooterEnc(17, true);
// pros::Optical optical(13, 40);

// Digital I/O
pros::ADIDigitalOut leftWing('F', false);
pros::ADIDigitalOut rightWing('G', false);
pros::ADIDigitalOut leftClimb('C', false);
pros::ADIDigitalOut rightClimb('D', false);
// pros::ADIDigitalOut bandRelease('E', false);
