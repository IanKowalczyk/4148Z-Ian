#include "lib_header/motion_h/move.h"

// ******** PID gains ******** //
PID drivePID(8, 12);        // Error units are in INCHES
PID turnPID(1.5, 7);        // Error units are in DEGREES   // 1.5, 4.5


// ******** Variables ******** //
double drive_position;
double drive_error;
double drive_target;
double turn_target;
int max_drive_power;
int max_turn_power;
bool drive_slew = false;
bool turn_slew = false;


// ******** Function ******** //
void move() {
    // Initialize timer
    int startTime = pros::c::millis();

    // Local variables 
    double initialPosition = (frontEnc.get_position() / 100) * wheelDegreeToInch(TRACKING_WHEEL_DIAMETER);
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

        // drive_position = rightFrontDrive.get_position() * wheelDegreeToInch(TRACKING_WHEEL_DIAMETER);
        drive_position = ((frontEnc.get_position() / 100) * wheelDegreeToInch(TRACKING_WHEEL_DIAMETER)) - initialPosition; // in inches
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
                settleCount++;
            }
            else {settleCount = 0;}
        }
        else if(std::fabs(turn_target) > 0 && drive_target == 0) {   // If turn only, check turn error
            if(std::fabs(turnError) < TURN_SETTLE_THRESHOLD) {
                settleCount++;
            }
            else {settleCount = 0;}
        }
        else if(std::fabs(drive_target) > 0 && std::fabs(turn_target) > 0) { // If both drive & turn, check both errors
            if(std::fabs(drive_error) < DISTANCE_SETTLE_THRESHOLD && std::fabs(turnError) < TURN_SETTLE_THRESHOLD) {
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


// ******** Setters ******** //
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


// ******** Chained Setters ******** //
void chainMove(std::vector<double> target1, std::vector<double> power1, int maxTime1, 
                std::vector<double> target2, std::vector<double> power2, int maxTime2, double threshold) {
    // First move
    setMove(target1[0], target1[1], power1[0], power1[1], maxTime1);
    waitUntilNear(threshold, 0);

    // Chain to second move
    setMove(target2[0], target2[1], power2[0], power2[1], maxTime2);
}

void extendMove(double driveTarget, double turnTarget, int maxDrivePower, int maxTurnPower, int maxTime) {
    drive_target = driveTarget;
    turn_target = turnTarget;
    max_drive_power = maxDrivePower;
    max_turn_power = maxTurnPower;
    max_time += maxTime;
}