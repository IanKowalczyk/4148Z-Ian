#include "lib_header/subsystems_h/drive.h"

// ******** Drive Constants ******** //
double TURN_SENS = 0.8;
double DRIVE_BRAKE_THRESHOLD = 45;  // 45 RPM


// ******** Drive Helper Functions ******** //

void setDrive(int leftVolt, int rightVolt) {
    leftDrive.move(leftVolt);
    rightDrive.move(rightVolt);
}
void setDriveBrakeMode(pros::motor_brake_mode_e brakeMode) {
    leftDrive.set_brake_modes(brakeMode);
    rightDrive.set_brake_modes(brakeMode);
}
void stopDrive(pros::motor_brake_mode_e brakeMode) {
    setDriveBrakeMode(brakeMode);
    leftDrive.brake();
    rightDrive.brake();
}

// ******** Drive Opcontrol functions ******** //
void splitArcade(pros::motor_brake_mode_e_t driveBrakeMode) {
    setDriveBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    // Read inputs from joysticks 
    double forwardPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double turnPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * TURN_SENS;
    // Deadzone to prevent drift
    if(fabs(forwardPower) <= 15) { forwardPower = 0;}
    if(fabs(turnPower) <= 15) { turnPower = 0;}
    // Output 
    setDrive(forwardPower + turnPower, forwardPower - turnPower);
}

void curveSplitArcade() {

}

// PTO Opcontrol
void drivePtoOpControl() {
    // // static bool sixMotorMode = states.driveStateIs(stateMachine::drive_state::SIX_MOTOR);
    // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
    //     if(states.driveStateIs(stateMachine::drive_state::SIX_MOTOR)) {
    //         states.setDriveState(stateMachine::drive_state::TWO_MOTOR);
    //     }
    //     else {
    //         states.setDriveState(stateMachine::drive_state::SIX_MOTOR);
    //     }
    // }
}

