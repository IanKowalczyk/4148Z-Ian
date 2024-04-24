#include "lib_header/subsystems_h/shooter.h"

// Variables
int pullbackCount = 0;

// Matchload variables
bool matchloadState = false;
int triballsFired = 0;
int triballFireTarget = 0;

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
void shooterOpControl(pros::controller_digital_e_t shootButton) {
    if(controller.get_digital_new_press(shootButton) && oneIntakeMode) {
        if(states.shooterStateIs(stateMachine::shooter_state::PULLED_BACK)) {
            states.setShooterState(stateMachine::shooter_state::FIRE);
        }
    }
}

void matchloadOpControl(pros::controller_digital_e_t matchloadButton) {
    // // static bool localMatchloadState = matchloadState;
    if(controller.get_digital_new_press(matchloadButton) && oneIntakeMode) {
        matchloadState = !matchloadState;
        controller.rumble("-");
    }
}
