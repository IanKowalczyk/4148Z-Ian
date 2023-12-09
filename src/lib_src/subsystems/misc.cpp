#include "lib_header/subsystems_h/misc.h"

// Variables
bool brakeReady = false;

// Wing opcontrol
bool wingsOut = false;
void wingOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        wingsOut = !wingsOut;
    }
    if(wingsOut) {
        states.setWingState(stateMachine::wing_state::WINGS_OUT);
    }
    else {
        states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    }
}

// Parking Brake opcontrol
bool brakeOn = false;
void brakeOpControl() {
    // if(brakeReady) {
    //     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    //         parkingBrakeOn = !parkingBrakeOn;
    //     }
    //     if(parkingBrakeOn) {
    //         states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_ON);
    //     }
    //     else {
    //         states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
    //     }
    // }
}

// Climb opcontrol
bool climbState = false;
void climbOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        climbState = !climbState;
        climb.set_value(climbState);
    }
}
