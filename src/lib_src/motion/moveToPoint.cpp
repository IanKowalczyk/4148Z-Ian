#include "lib_header/motion_h/moveToPoint.h"

// ******** PID gains ******** //
PID translationPID(7.9, 13);    // Error units are in INCHES    // 7, 18
PID rotationPID(1.5, 7);        // Error units in DEGREES


// ******** Variables ******** //
double translation_error;
double target_x;
double target_y;
double end_orientation;
int max_translate_power;
int max_rotate_power;
int max_orient_power;
bool movement_reversed = false; // drive forward by default


// ******** Function ******** //
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
            // targetAngle = fmod((90 - (atan2(yError, xError) * RAD_TO_DEG)), 360) + 180;
            targetAngle = (atan2(xError, yError) * RAD_TO_DEG) + 180;
        }
        else { // forward
            // targetAngle = fmod((90 - (atan2(yError, xError) * RAD_TO_DEG)), 360);
            targetAngle = atan2(xError, yError) * RAD_TO_DEG;
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
        movementScaleFactor = cos(fmod(rotationError, 90) * DEG_TO_RAD); // should change to cos( std::min(int(rotationError), 90) ) * DEG_TO_RAD)

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
        std::fabs(translation_error) > 7 ? rotationPower = round(rotationPID.calculateOutput(rotationError)) : rotationPower = 0; 

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
            rotationPID.reset();
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


// ******** Setters ******** //
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
    rotationPID.reset();
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


// ******** Chained Setters ******** //
void chainMoveToPoint(std::vector<double> pose1, std::vector<double> power1, int maxTime1, 
                        std::vector<double> pose2, std::vector<double> power2, int maxTime2, double threshold) {
    setMoveToPoint(pose1[0], pose1[1], power1[0], power1[1], maxTime1, true);
    waitUntilNear(threshold, 0);
    setMoveToPoint(pose2[0], pose2[1], power2[0], power2[1], maxTime2, true);
}

void extendMoveToPoint(double targetX, double targetY, int maxTranslatePower, int maxRotatePower, int maxTime, bool reversed) {
    target_x = targetX;
    target_y = target_y;
    max_translate_power = maxTranslatePower;
    max_rotate_power = maxRotatePower;
    max_time += max_time;
    movement_reversed = reversed;
}