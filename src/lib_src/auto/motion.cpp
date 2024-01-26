#include "lib_header/auto_h/motion.h"
// #include <cmath>
// #include <vector>

// TO DO
// Implement acceleration cap / maybe deaccel
// Boomerange alg
// synchronize tasks using pros::Task::delay_until for consistent loop execution
// Make curve function async
// Path following alg 

// **** Useful info **** //
// NO SLEW: travels 24in in 605 ms: 39.67 in/s
// SLEW:    travels 24in in 
	// tuning pid
	// setMove(24, 0, 120, 0, 2000, false, false, false);   // 605 ms
	// setMove(24, 0, 120, 0, 2000, false, true, false);    // 638 ms
	// setMove(0, 180, 0, 100, 1000);       // ~ 700 ms sometimes, 1000 ms sometimes else????
	// setMove(0, 90, 0, 100, 1000);        // 500 ms
	// setMoveToPoint(0, 24, 1000, false);  // 750 ms

double IDEAL_DRIVE_VELOCITY = 39.67; // Inches per second
double IDEAL_TURN_VELOCITY = 180;    // Degrees per second

// **************** Movement Constants **************** //
int DRIVE_SLEW_RATE = 120/15;   // 150 ms to accelerate = 15 iterations; 120 (basically max power) / 15 (iterations)
int TURN_SLEW_RATE = 120/15;    // 150 ms to accelerate ... TUNE LATER
int SETTLE_THRESHOLD = 5;       // 50 ms: 5 iterations * 10 ms loop // Used to be 50ms
int NEAR_TARGET_THRESHOLD = 2;          // 2 inches
double DISTANCE_SETTLE_THRESHOLD = 1;   // 1 inch
double TURN_SETTLE_THRESHOLD = 1.5;       // 1.5 degrees


// **************** PID Objects **************** //

PID drivePID(8, 12);        // Error units are in INCHES
PID translationPID(7.9, 13);  // Error units are in INCHES    // 7, 18
PID turnPID(1.5, 7);        // Error units are in DEGREES   // 1.5, 4.5


// **************** Movement Variables **************** //
// move() variables
double drive_position;
double drive_error;
double drive_target;
double turn_target;
int max_drive_power;
int max_turn_power;
bool drive_slew = false;
bool turn_slew = false;

// moveToPoint() variables
double translation_error;
double target_x;
double target_y;
double end_orientation;
int max_translate_power;
int max_rotate_power;
int max_orient_power;
bool movement_reversed = false; // drive forward by default

// curve() variables
double radius;

// Universal variables 
bool driveSettled = true; // false?
bool nearTarget = false;
bool full_power = false;
int max_time = 2000;

// **************** Setters for Movement Functions **************** //

void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime, bool fullPower, bool driveSlew, bool turnSlew) {
    // Disable autoMovement
    states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
    driveSettled = false;
    pros::delay(10); //20 ms

    // Set targets
    drive_target = driveTarget;
    turn_target = turnTarget;
    max_drive_power = maxDrivePower;
    max_turn_power = maxTurnPower;
    max_time = maxTime;
    
    // // Movement flag
    fullPower ? full_power = true : full_power = false;
    // currentMovementFlag = flag;

    // Set slew
    driveSlew ? drive_slew = true : drive_slew = false;
    turnSlew  ? turn_slew = true : turn_slew = false;

    // // Reset error
    // drive_error = 0;

    // Set state
    // nearTarget = false;
    driveSettled = false;
    states.setDriveAutoState(stateMachine::drive_auto_state::MOVE);
}

void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime, bool fullPower) {
    setMove(driveTarget, turnTarget, maxDrivePower, maxTurnPower, maxTime, fullPower, true, false);
}

void setMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime) {
    setMove(driveTarget, turnTarget, maxDrivePower, maxTurnPower, maxTime, false, true, false);
}

void setMove(double driveTarget, double turnTarget, int maxTime) {
    setMove(driveTarget, turnTarget, 100, 100, maxTime, false, true, false);
}

void setMoveToPoint(double targetX, double targetY, double endOrientation, int maxTranslatePower, 
        int maxRotatePower, int maxOrientPower, int maxTime, bool reversed) {
    // Disable autoMovement
    states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
    driveSettled = false;
    pros::delay(10); // 10 ms

    // Colored box for debugging
    // pros::screen::set_eraser(COLOR_BLACK);
    // pros::screen::erase();
    // pros::screen::set_pen(COLOR_GREEN);
    // pros::screen::fill_rect(5,5,240,200);

    // Set targets
    target_x = targetX;
    target_y = targetY;
    end_orientation = endOrientation;
    max_translate_power = maxTranslatePower;
    max_rotate_power = maxRotatePower;
    max_orient_power = maxOrientPower;
    max_time = maxTime;

    // // Movement flag
    // currentMovementFlag = flag;
    reversed ? movement_reversed = true : movement_reversed = false;

    // // Reset error
    translationPID.reset();
    turnPID.reset();
    translation_error = 0;

    // Set state
    // nearTarget = false;
    driveSettled = false;
    states.setDriveAutoState(stateMachine::drive_auto_state::MOVE_TO_POINT);
}
void setMoveToPoint(double targetX, double targetY, int maxTranslatePower, int maxRotatePower,  int maxTime, bool reversed) {
    setMoveToPoint(targetX, targetY, 0, maxTranslatePower, maxRotatePower, 0, maxTime, reversed);
}
void setMoveToPoint(double targetX, double targetY, int maxTime, bool reversed) {
    setMoveToPoint(targetX, targetY, 0, 100, 100, 0, maxTime, reversed);
}

// void curve() {
//     int startTime = pros::c::millis();

//     int stepCount = 50;
//     double angleError = turn_target - inertial.get_heading();  // calculate error to endAngle

//     double arcLength = 2 * M_PI * radius * (std::fabs(angleError) / 360); // use error to endAngle to find arc length to travel
   
//     double arcLengthStep = arcLength / stepCount;   // define step for arclength
//     double tempArcLength = arcLengthStep;           // will be used to check when to iterate angle

//     double angleStep = angleError / stepCount;      // define step for angle
//     double tempAngle = inertial.get_heading() + angleStep;  // used to get arc started

//     double driveError, turnError;
//     double drivePower, turnPower;
//     double currentPosition = (frontEnc.get_position() / 100) * DRIVE_DEG_TO_INCH_2IN;
    
//     while(true) {
//         driveError = 
//         pros::delay(10);
//     }
// }


void setCurve(double distance, double endAngle, double radius, int maxDrivePower, int maxTurnPower, int maxTime) {
    int stepCount = 50; // How many "slices" to divide the arc into

    double angleError = endAngle - inertial.get_heading();  // calculate error to endAngle
    double arcLength = 2 * M_PI * radius * (std::fabs(angleError) / 360); // use error to endAngle to find arc length to travel

    double arcLengthStep = arcLength / stepCount;   // define step for arclength
    double tempArcLength = arcLengthStep;           // will be used to check when to iterate angle

    double angleStep = angleError / stepCount;      // define step for angle
    double tempAngle = inertial.get_heading() + angleStep;  // used to get arc started

//  * returnSign(angleError)
    setMove(arcLength + distance, tempAngle, maxDrivePower, maxTurnPower, maxTime, false, false, false); // arcLength + distance
    
    for(int i = 0; i < stepCount - 1; i++) {    // step count - 2, so that we have time to add distance after arc before exiting move function
        while(drive_position < tempArcLength) {
            pros::delay(1);
        }
		turn_target += angleStep;
        tempArcLength += arcLengthStep;
        if(tempArcLength > arcLength) {tempArcLength = arcLength;}
		pros::delay(5);
	}
    turn_target = endAngle;
}

// ******** Chained Movement Function ******** //
void chainMove(std::vector<double> target1, std::vector<double> power1, int maxTime1, 
                std::vector<double> target2, std::vector<double> power2, int maxTime2, double threshold) {
    // First move
    setMove(target1[0], target1[1], power1[0], power1[1], maxTime1);
    waitUntilNear(threshold, 0);

    // Chain to second move
    setMove(target2[0], target2[1], power2[0], power2[1], maxTime2);
}

void chainMoveToPoint(std::vector<double> pose1, std::vector<double> power1, int maxTime1, 
                        std::vector<double> pose2, std::vector<double> power2, int maxTime2, double threshold) {
    setMoveToPoint(pose1[0], pose1[1], power1[0], power1[1], maxTime1, true);
    waitUntilNear(threshold, 0);
    setMoveToPoint(pose2[0], pose2[1], power2[0], power2[1], maxTime2, true);
}

// ******** Wait Functions ******** //
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

// **************** Auto Movement Task **************** //

void autoMovementTask() {
    // states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
    while(true) {
        if(states.driveAutoStateIs(stateMachine::drive_auto_state::OFF)) {
            // pros::delay(5);
            // while(!states.driveAutoStateChanged) {pros::delay(5);}
        }
        else if(states.driveAutoStateIs(stateMachine::drive_auto_state::MOVE)) {
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
        pros::delay(5);
    }
}


// **************** Movement Functions **************** //

void move() {
    // Initialize timer
    int startTime = pros::c::millis();

    // Local variables 
    double initialPosition = (frontEnc.get_position() / 100) * DRIVE_DEG_TO_INCH_2IN;
    // double currentPosition;
    int turnError = 0;
    int drivePower, turnPower;
    int tempDriveMax = 30;
    int tempTurnMax = 30;
    bool stopLoop = false;
    int settleCount = 0;

    // Reset variables
    drive_error = 0.0;
    driveSettled = false;

    // Slew conditionals
    if(std::fabs(drive_target) < 12.5) {drive_slew = false;}
    
    // Feedforward
    double turnFF = 1;
    double driveFF = 1;
    int initialDriveError = drive_target;
    int initialTurnError = std::floor(turn_target - inertial.get_heading());

    while(!driveSettled) {
        fabs(initialTurnError) < 65 ? turnFF = 2 : turnFF = 1;
        fabs(initialDriveError) < 12.5 ? driveFF = 2 : driveFF = 1;
        // currentPosition = ((frontEnc.get_position() / 100) * DRIVE_DEG_TO_INCH) - initialPosition;
        // driveError = driveTarget - (frontEnc.get_position() * DRIVE_DEG_TO_INCH);

        // drive_position = rightFrontDrive.get_position() * DRIVE_DEG_TO_INCH_2IN;
        drive_position = ((frontEnc.get_position() / 100) * DRIVE_DEG_TO_INCH_2IN) - initialPosition; // in inches
        // drive_error = int(drive_target - drive_position);
        drive_error = drive_target - drive_position;
        turnError = turn_target - inertial.get_heading();

        // Constrain relative turn from 180 to -180
        if(turnError > 180) {turnError -= 360;}
        if(turnError < -180) {turnError += 360;}

        // Calculate PID outputs 
        if(full_power) {
            drivePower = max_drive_power * getSign(drive_error);
        }
        else {
            drivePower = int(drivePID.calculateOutput(drive_error)) * driveFF; //, max_drive_power, -max_drive_power
        }
        turnPower = int(turnPID.calculateOutput(turnError)) * turnFF; //, max_turn_power, -max_turn_power

        // Slew rate logic
        if(drive_slew) {
            // Only increment if temp drive power is less than max drive power
            if(tempDriveMax <= max_drive_power) {
                tempDriveMax += DRIVE_SLEW_RATE;
                drivePower = constrainValue(drivePower, tempDriveMax, -tempDriveMax);
            }
            else {
                // Drive slew is done
                drive_slew = false;
            }
        }
        // if(turn_slew) { 
        //     // Only increment if temp turn power is less than max turn power
        //     if(tempTurnMax <= max_turn_power) {
        //         tempTurnMax += TURN_SLEW_RATE;
        //         turnPower = constrainValue(turnPower, tempTurnMax, -tempTurnMax);
        //     }
        //     else {
        //         // Turn slew is done
        //         turn_slew = false;
        //     } 
        // }

        // Constrain PID outputs
        drivePower = constrainVoltage(drivePower, max_drive_power, -max_drive_power);
        turnPower = constrainVoltage(turnPower, max_turn_power, -max_turn_power);

        // Exit conditions
        if(std::fabs(drive_target) > 0 && max_turn_power == 0) {   // If drive only, check drive error
            if(std::fabs(drive_error) < DISTANCE_SETTLE_THRESHOLD) {
                nearTarget = true;
                settleCount++;
            }
            else {settleCount = 0;}
        }
        else if(std::fabs(turn_target) > 0 && drive_target == 0) {   // If turn only, check turn error
            if(std::fabs(turnError) < TURN_SETTLE_THRESHOLD) {
                nearTarget = true;
                settleCount++;
            }
            else {settleCount = 0;}
        }
        else if(std::fabs(drive_target) > 0 && std::fabs(turn_target) > 0) { // If both drive & turn, check both errors
            if(std::fabs(drive_error) < DISTANCE_SETTLE_THRESHOLD && std::fabs(turnError) < TURN_SETTLE_THRESHOLD) {
                nearTarget = true;
                settleCount++;
            }
            else {settleCount = 0;}
        }
        if((settleCount >= SETTLE_THRESHOLD) || (pros::c::millis() - startTime) >= max_time) {
            // pros::screen::erase_line(0, 8, 600, 9);
            // pros::screen::print(TEXT_MEDIUM_CENTER, 8, "Movement time: %d", pros::c::millis() - startTime);
            // pros::delay(50000);

            stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
            drive_error = turnError = drivePower = turnPower = 0;
            drive_position = drive_target = turn_target = 0;
            drivePID.reset();
            turnPID.reset();
            driveSettled = true;
            states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
            break;
        }

        // Output to drive
        setDrive(drivePower + turnPower, drivePower - turnPower); // NORMAL BOT

        // Debug 
        // if(!pros::competition::is_disabled()) {
            pros::screen::erase_line(0, 1, 600, 1);
            pros::screen::print(TEXT_MEDIUM_CENTER, 1, "Drive Target: %3.1f, Err: %3.2f, Out: %3d", drive_target, drive_error, drivePower);
            pros::screen::erase_line(0, 2, 600, 2);
            pros::screen::print(TEXT_MEDIUM_CENTER, 2, "Turn Tgt: %3.1f, Err: %3.2f, Out: %3d", turn_target, turnError, turnPower);
            pros::screen::erase_line(0, 2, 600, 3);
            pros::screen::print(TEXT_MEDIUM_CENTER, 3, "Turn: FF: %1.1f,  init Err: %3d", turnFF, initialTurnError);
            pros::screen::erase_line(0, 3, 600, 4);
            pros::screen::print(TEXT_MEDIUM_CENTER, 4, "Drive: FF: %1.1f, init Err: %3d", driveFF, initialDriveError);

        // }
        
        // necessary delay - do not change
        pros::delay(10);
    }
    // // Reset
    // drive_error = turnError = drivePower = turnPower = 0;
    // drivePID.reset();
    // turnPID.reset();
}

void moveToPoint() {
    // Initialize timer
    int startTime = pros::c::millis();

    // Local variables 
    double targetAngle, rotationError, orientationError;
    int translationPower, rotationPower, orientationPower;
    double movementScaleFactor;
    double xError = 0.0;
    double yError = 0.0;
    int settleCount = 0;
    int tempDriveMax = 30;

    // Reset variables
    translation_error = 0.0;
    driveSettled = false;
    bool onTarget = false;

    while(!driveSettled) {
        // Calculate point errors
        xError = target_x - globalPose.x;
        yError = target_y - globalPose.y;

        // Calculate distance and angle, check if movement is reversed
        if(movement_reversed) { // reversed, add 180 to angle
            targetAngle = fmod((90 - (atan2(yError, xError) * RAD_TO_DEG)), 360) + 180;
        }
        else { // forward
            targetAngle = fmod((90 - (atan2(yError, xError) * RAD_TO_DEG)), 360);
        }
        // targetAngle = 90 - (atan2(yError, xError) * RAD_TO_DEG);

        // Calculate movement errors
        if(movement_reversed) { // reverse drive direction
            translation_error = -hypot(xError, yError);
        }
        else { // forward
            translation_error = hypot(xError, yError);
        }
        rotationError = targetAngle - (globalPose.theta * RAD_TO_DEG);
        if(rotationError > 180) {rotationError -= 360;}
        if(rotationError < -180) {rotationError += 360;}

        // Scale factor to prioritize turning
        movementScaleFactor = cos(fmod(rotationError, 90) * DEG_TO_RAD);

        // translate power
        translationPower = round(translationPID.calculateOutput(translation_error) * movementScaleFactor);
        translationPower = constrainVoltage(translationPower, std::fabs(movementScaleFactor) * max_translate_power, -std::fabs(movementScaleFactor) * max_translate_power);
        
        // Slew
        translationPower = constrainVoltage(translationPower, tempDriveMax, -tempDriveMax);
        if(tempDriveMax <= max_translate_power - DRIVE_SLEW_RATE) {
            tempDriveMax += DRIVE_SLEW_RATE;
        }

        
        // Rotate power
        // Stop rotating when close to target // used to be within 2.5 inches, now 3.5
        std::fabs(translation_error) > 7 ? rotationPower = round(turnPID.calculateOutput(rotationError)) : rotationPower = 0; 

        // Constrain outputs
        // translationPower = constrainVoltage(translationPower, max_translate_power, -max_translate_power);
        rotationPower = constrainVoltage(rotationPower, max_rotate_power, -max_rotate_power);
        
        // Near target conditional
        // translation_error <= NEAR_TARGET_THRESHOLD ? nearTarget = true : nearTarget = false;
        
        // Increment settle count if 'on' target (< 0.6 inches)
        std::fabs(translation_error) < 1.2 ? settleCount ++ : settleCount = 0;

        // Exit condition
        if(settleCount >= SETTLE_THRESHOLD || (pros::c::millis() - startTime) >= max_time) {
            // pros::screen::erase_line(0, 8, 600, 9);
            // pros::screen::print(TEXT_MEDIUM_CENTER, 8, "Movement time: %d", pros::c::millis() - startTime);
            // pros::delay(50000);

            stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
            translation_error = translationPower = rotationError = rotationPower = 0;
            translationPID.reset();
            turnPID.reset();
            driveSettled = true;
            states.setDriveAutoState(stateMachine::drive_auto_state::OFF);
            break;
        }

        // Output
        // setDrive(-translationPower - rotationPower, -translationPower + rotationPower); // MINI BOT
        setDrive(translationPower + rotationPower, translationPower - rotationPower); // NORMAL BOT

        // if(!pros::competition::is_disabled()) {  // debug
            pros::screen::erase_line(0, 1, 400, 2);
            pros::screen::print(TEXT_MEDIUM_CENTER, 1, "Tgt: x: %3.1f, y: %3.1f, theta: %3.1f", target_x, target_y, targetAngle);
            pros::screen::erase_line(0, 2, 400, 3);
            pros::screen::print(TEXT_MEDIUM, 2, "dist err: %3.1f, volt: %3d, ang err: %3.1f, volt: %3d", translation_error, translationPower, rotationError, rotationPower);
        // }

        // necessary delay
        pros::delay(10);
    }
}

void turn() {
    int turnError;
    int turnPower;
    int startTime = pros::c::millis();
    while(!driveSettled) {
        // Calculate and constrain error
        // turnError = turn_target - inertial.get_heading();
        turnError = constrainAngle180(turn_target - inertial.get_heading());
        
        // Calculate and constrain turn power
        turnPower = turnPID.calculateOutput(turnError);
        turnPower = constrainValue(turnPower, max_turn_power, -max_turn_power);

        // Exit conditions
        if(std::fabs(turnError) <= TURN_SETTLE_THRESHOLD || (pros::c::millis() - startTime) > max_time) {
            stopDrive(pros::E_MOTOR_BRAKE_BRAKE);
            turnPID.reset();
            driveSettled = true;
        }


        if(pros::competition::is_autonomous()) {
        pros::screen::erase_line(0, 3, 300, 3);
        pros::screen::print(TEXT_MEDIUM_CENTER, 3, "Turn Target: %i, Error: %i, Output: %i", turn_target, turnError, turnPower);
        }

        // necessary delay - do not change
        pros::delay(20);
    }
}
