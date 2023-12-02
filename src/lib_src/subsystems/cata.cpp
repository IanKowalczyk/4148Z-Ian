#include "lib_header/subsystems_h/cata.h"

// Constants
int SHORT_PULLBACK_TICKS = 0;   // In centidegrees (100 * degrees) 
int FULL_PULLBACK_TICKS = 0;     // In centidegrees (100 * degrees) 
int PULLBACK_TIMEOUT = 1000;    // 1000 ms
int PULLBACK_THRESHOLD = 2500;  // 2500 - How close we want to get to the pullback value before stopping the puncher (to mitigate overshoot)

// Variables
int pullbackCount = 0;

// Matchload variables
bool matchloadState = false;
int fireCount = 0;
int fireTarget = 0;


// **** Helper functions **** //
void setCata(int volt) {
    cataMotors.move(volt);
}
void setCataBrakeMode(pros::motor_brake_mode_e brakeMode) {
    cataMotors.set_brake_modes(brakeMode);
}
void stopCata(pros::motor_brake_mode_e brakeMode) {
    setCataBrakeMode(brakeMode);
    cataMotors.brake();
}

// **** Cata **** //
void fire(int numTimes, int newPullback) {

}

void setMatchload(int numTimes, bool waitForCompletion) {
    // fireCount = 0;
    // fireTarget = numTimes;
    // matchloadState = true;
    // if(waitForCompletion) 
    // {
    //     while(fireCount < fireTarget) {pros::delay(5);}
    //     matchloadState = false;
    //     pros::delay(50);
    // }
}

// void shooterTask() {}


// **** Op control **** //
void cataOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        if(states.cataStateIs(stateMachine::cata_state::PULLED_BACK)) {
            states.setCataState(stateMachine::cata_state::FIRE);
        }
    }
}

void matchloadOpControl() {
    // // static bool localMatchloadState = matchloadState;
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        matchloadState = !matchloadState;
        controller.rumble("-");
    }
}
