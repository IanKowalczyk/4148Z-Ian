#include "lib_header/subsystems_h/intake.h"

// ******** Intake Variables ******** //
int openCount = 0;
int closeCount = 0;


// ******** Intake Helper Functions ******** //
// void setIntake(int intakeVolt) {
//     intake.move(intakeVolt);
// }
// void setIntakeBrakeMode(pros::motor_brake_mode_e brakeMode) {
//     intake.set_brake_mode(brakeMode);
// }
// void stopIntake(pros::motor_brake_mode_e_t brakeMode) {
//     setIntakeBrakeMode(brakeMode);
//     intake.brake();
// }

// ******** Intake Opcontrol function ******** //
void intakeOpControl(pros::controller_digital_e_t intakeButton, pros::controller_digital_e_t outtakeButton) {
    if(controller.get_digital(intakeButton)) {
        states.setIntakeState(stateMachine::intake_state::INTAKING);
    }
    else if(controller.get_digital(outtakeButton)) {
        states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    }
    else {states.setIntakeState(stateMachine::intake_state::OFF);}
}


