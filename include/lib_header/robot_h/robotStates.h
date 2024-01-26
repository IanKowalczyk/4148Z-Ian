#ifndef ROBOT_STATES_H
#define ROBOT_STATES_H
#include "main.h"
// #include <string>

/** @brief State Machine that holds all subsystem states */
struct stateMachine{
private:
public:
    // Subsystem states
    // enum class drive_state {TWO_MOTOR, SIX_MOTOR} driveState, oldDriveState;
    // const char* driveStateString[2] = {"TWO MOTOR", "SIX MOTOR"};

    enum class intake_state {OFF, INTAKING, OUTTAKING} intakeState, oldIntakeState;
    const char* intakeStateString[3] = {"OFF", "INTAKING", "OUTTAKING"};

    enum class shooter_state {FIRE, SHORT_PULLBACK, PULLED_BACK} shooterState, oldShooterState, defaultPullback = shooter_state::SHORT_PULLBACK;
    // const char* cataStateString[2] = {"FIRE", "PULLED BACK"};
    // const char* pullbackStateString[3] = {"SHORT", "MID", "LONG"};

    // enum puncher_angle_state {STEEP, MID, FLAT, DOWN} puncherAngleState, oldPuncherAngleState;
    // const char* angleStateString[4] = {"STEEP", "MID", "FLAT", "DOWN"};

    enum class wing_state {WINGS_OUT, WINGS_STOWED, LEFT_OUT, RIGHT_OUT} wingState, oldWingState;
    const char* wingStateString[4] = {"WINGS OUT", "WINGS IN", "LEFT OUT", "RIGHT OUT"};

    enum class parking_brake_state {BRAKE_ON, BRAKE_OFF} parkingBrakeState, oldParkingBrakeState;
    const char* parkingBrakeStateString[2] = {"BRAKES ON", "BRAKES OFF"};

    // Drive auto states
    enum class drive_auto_state{OFF, MOVE, TURN, CURVE, MOVE_TO_POINT, MOVE_TO_POSE} driveAutoState;
    
    // Alliance color
    enum class alliance_color {RED_ALLIANCE, BLUE_ALLIANCE} allianceColor, oldAllianceColor; 

    // Drive
    // void setDriveState(drive_state s) {driveState = s;}
    // // int getDriveState() {return driveState;}
    // bool driveStateIs(drive_state s) {return(s == driveState);}
    // bool driveStateChanged() {return(oldDriveState != driveState);}

    // Intake
    void setIntakeState(intake_state s) {intakeState = s;}
    // int getIntakeState() {return intakeState;}
    bool intakeStateIs(intake_state s) {return(s == intakeState);}
    bool intakeStateChanged() {return(oldIntakeState != intakeState);}

    // Cata
    void setShooterState(shooter_state s) {shooterState = s;}
    // int getCataState() {return cataState;}
    bool shooterStateIs(shooter_state s) {return(s == shooterState);}
    bool shooterStateChanged() {return(oldShooterState != shooterState);}

    // Puncher angle
    // void setPuncherAngleState(puncher_angle_state s) {puncherAngleState = s;}
    // // int getPuncherAnglerState() {return puncherAngleState;}
    // bool puncherAngleStateIs(puncher_angle_state s) {return(s == puncherAngleState);}
    // bool puncherAngleStateChanged() {return(oldPuncherAngleState != puncherAngleState);}

    // Wing
    void setWingState(wing_state s) {wingState = s;}
    // int getWingState() {return wingState;}
    bool wingStateIs(wing_state s) {return(s == wingState);}
    bool wingStateChanged() {return(oldWingState != wingState);}

    // Parking brake
    void setParkingBrakeState(parking_brake_state s) {parkingBrakeState = s;}
    // int getParkingBrakeState() {return parkingBrakeState;}
    bool parkingBrakeStateIs(parking_brake_state s) {return(s == parkingBrakeState);}
    bool parkingBrakeStateChanged() {return(oldParkingBrakeState != parkingBrakeState);}
    
    // Drive auto states
    void setDriveAutoState(drive_auto_state s) {driveAutoState = s;}
    bool driveAutoStateIs(drive_auto_state s) {return(s == driveAutoState);}

    // Alliance color
    void setAllianceColor(alliance_color s) {allianceColor = s;}
    bool allianceColorIs(alliance_color s) {return(s == allianceColor);}
    bool allianceColorChanged() {return(oldAllianceColor != allianceColor);}
};

/** @brief State Machine Object*/
extern stateMachine states;

/** @brief Task that handles all subsystem states */
extern void stateHandler();

/** @brief Flag to run state handler task*/
extern bool runStateHandler;

/** @brief State Machine task */
// extern pros::Task stateMachineTask(stateHandler);

#endif