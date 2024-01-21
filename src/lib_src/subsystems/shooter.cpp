#include "lib_header/subsystems_h/shooter.h"

// Constants
int SHORT_PULLBACK_TICKS = 4500;   // In centidegrees (100 * degrees)  // 4800
int FULL_PULLBACK_TICKS = 0;     // In centidegrees (100 * degrees) 
int MIN_FIRE_TIME = 200;
int PULLBACK_TIMEOUT = 1000;    // 1000 ms
int PULLBACK_THRESHOLD = 700;  // How close we want to get to the pullback value before stopping the cata (to mitigate overshoot)

// Variables
int pullbackCount = 0;

// Matchload variables
bool matchloadState = false;
int fireCount = 0;
int fireTarget = 0;


// **** Helper functions **** //
void setShooter(int volt) {
    shooterMotors.move(volt);
}
void setShooterBrakeMode(pros::motor_brake_mode_e brakeMode) {
    shooterMotors.set_brake_modes(brakeMode);
}
void stopShooter(pros::motor_brake_mode_e brakeMode) {
    setShooterBrakeMode(brakeMode);
    shooterMotors.brake();
}

// **** Shooter **** //
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
void shooterOpControl() {
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        if(states.shooterStateIs(stateMachine::shooter_state::PULLED_BACK)) {
            states.setShooterState(stateMachine::shooter_state::FIRE);
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
