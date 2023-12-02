#include "lib_header/subsystems_h/intake.h"

// ******** Intake Constants ******** //
int INTAKE_CLOSE_THRESHOLD = 300;   // 200 ms
int INTAKE_OPEN_THRESHOLD = 200;    // 200 ms

// ******** Intake Variables ******** //
int openCount = 0;
int closeCount = 0;


// ******** Intake Helper Functions ******** //
// void spinIntake(int intakeVolt) {
//     cataMotors.move(intakeVolt);
// }
// void setIntakeBrakeMode(pros::motor_brake_mode_e brakeMode) {
//     leftDrive.set_brake_modes(brakeMode);
//     rightDrive.set_brake_modes(brakeMode);
// }
// void stopIntake(pros::motor_brake_mode_e_t brakeMode) {
//     setIntakeBrakeMode(brakeMode);
//     cataMotors.brake();
// }

// ******** Intake Opcontrol function ******** //
void intakeOpControl() {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        states.setIntakeState(stateMachine::intake_state::INTAKING);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    }
    else {states.setIntakeState(stateMachine::intake_state::OFF);}
}


