#include "lib_header/subsystems_h/misc.h"

// Variables
bool brakeReady = false;

// Wing opcontrol
bool wingsOut = false;
void wingOpControl(pros::controller_digital_e_t wingButton) {
    if(controller.get_digital_new_press(wingButton)) {
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
    if((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) || controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
    || controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        // if(states.climbStateIs(stateMachine::climb_state::DOWN)) {
        //     states.setClimbState(stateMachine::climb_state::UP);
        // }
        // else {
        //     states.setClimbState(stateMachine::climb_state::DOWN);
        // }
        climbState = !climbState;
        leftClimb.set_value(climbState);
        rightClimb.set_value(climbState);
    }
}

void climbUp() {
    leftClimb.set_value(true);
    rightClimb.set_value(true);
}

void climbDown() {
    leftClimb.set_value(false);
    rightClimb.set_value(false);
}