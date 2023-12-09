#include "lib_header/robot_h/robotStates.h"

stateMachine states;

void stateHandler() {
    // default states
    matchloadState = false;
    states.setIntakeState(stateMachine::intake_state::OFF);
    states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
    states.setCataState(stateMachine::cata_state::PULLED_BACK);

    // set sensor data rates
    inertial.set_data_rate(5);
    frontEnc.set_data_rate(5);
    sideEnc.set_data_rate(5);
    cataEnc.set_data_rate(5);
    
    // optical sensor initilization
    optical.set_integration_time(40);   // 40 ms data refresh rate
    optical.disable_gesture();
    // optical.set_led_pwm(100);           // brightness

    // odom initialization
    resetOdomSensors();
	globalPose.setPoint(0.0, 0.0, 0);

    // local variables
    int loopDelay = 10;
    int fireCount = 0;
    int intakeCount = 0;
    int rumbleCount = 0;
    int displayCount = 0;

    while(true) {
    int loopStartTime = pros::c::millis();

     // ******** Odometry ******** //
    // if(pros::competition::is_autonomous()) {
        updatePosition();
    // }

    // ******** Intake state handler ******** //
    if(states.intakeStateChanged()) {
        if(states.intakeStateIs(stateMachine::intake_state::OFF)) {
            stopCata(pros::E_MOTOR_BRAKE_BRAKE);
            intakeCount = 0;
        }
        else if(states.intakeStateIs(stateMachine::intake_state::INTAKING)) {
            setCata(127);
            // intakeCount += 10;
        }
        else if(states.intakeStateIs(stateMachine::intake_state::OUTTAKING)) {
            setCata(-127);
        }
        states.oldIntakeState = states.intakeState;
    }

    // If triball in intake, rumble controller
    if(states.intakeStateIs(stateMachine::intake_state::INTAKING)) {
        intakeCount += loopDelay;
        if(intakeCount > 200 && (leftCata.get_current_draw() + rightCata.get_current_draw())/2 > 1500) {
            // states.setIntakeState(stateMachine::intake_state::OFF);
            controller.rumble("-");
        }
    }
    else {intakeCount = 0;}


    // ******** Cata state handler ******** //
    if(states.cataStateChanged()) {
        if(states.cataStateIs(stateMachine::cata_state::FIRE)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "CATA FIRED");}
            setCata(-127);
            fireCount += loopDelay;
            if(fireCount > MIN_FIRE_TIME) {
                fireCount = 0;
                states.setCataState(stateMachine::cata_state::SHORT_PULLBACK);
            }
        }

        if(states.cataStateIs(stateMachine::cata_state::SHORT_PULLBACK)) {
            // if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 2, "SHORT PULLBACK, Volt: %d", cataMotors.get_voltages());}
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "PULLING BACK");}
            setCata(-127);
            if(cataEnc.get_position() > (SHORT_PULLBACK_TICKS - PULLBACK_THRESHOLD) || pullbackCount >= PULLBACK_TIMEOUT) { // 
                stopCata(pros::E_MOTOR_BRAKE_COAST);
                states.setCataState(stateMachine::cata_state::PULLED_BACK);
            }
            pullbackCount += loopDelay;
        }

        if(states.cataStateIs(stateMachine::cata_state::PULLED_BACK)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "PULLED BACK !!!!!!!");}
            // stopCata(pros::E_MOTOR_BRAKE_COAST);
            pullbackCount = 0;
            states.oldCataState = states.cataState;
        }
    }

        
    // ******** Wing state handler ******** //
    if(states.wingStateChanged()) {
        if(states.wingStateIs(stateMachine::wing_state::WINGS_STOWED)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "WINGS IN");}
            leftWing.set_value(false);
            rightWing.set_value(false);
        }
        else if(states.wingStateIs(stateMachine::wing_state::WINGS_OUT)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "WINGS OUT");}
            leftWing.set_value(true);
            rightWing.set_value(true);
        }
        else if(states.wingStateIs(stateMachine::wing_state::LEFT_OUT)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "LEFT WING OUT");}
            leftWing.set_value(true);
            rightWing.set_value(false);
        }
        else if(states.wingStateIs(stateMachine::wing_state::RIGHT_OUT)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 7, "RIGHT WING OUT");}
            leftWing.set_value(false);
            rightWing.set_value(true);
        }
        states.oldWingState = states.wingState;
    }

    // ******** Parking brake state handler ******** //
    // if(states.parkingBrakeStateChanged()) {
    //     if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_OFF)) {
    //         if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 8, "BRAKES OFF");}
    //         setDrive(0, 0);
    //         controller.rumble(".");
    //     }
    //     else if(states.parkingBrakeStateIs(stateMachine::parking_brake_state::BRAKE_ON)) {
    //         if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 8, "BRAKES ON");}
    //         setDrive(20, 20);
    //         leftFrontDrive.move(-20);
    //         rightFrontDrive.move(-20);
    //         controller.rumble(".");
    //     }
    //     states.oldParkingBrakeState = states.parkingBrakeState;
    // }

    // Drive check for engaging brakes
    // if(std::fabs(leftFrontDrive.get_actual_velocity()) + std::fabs(rightFrontDrive.get_actual_velocity()) < DRIVE_BRAKE_THRESHOLD) {
    //     brakeReady = true;
    // }
    // else {brakeReady = false;}


    // ******** Matchload ******** //
    if(matchloadState) {
        optical.set_led_pwm(100);
        // rumble every second to signal we are in matchload state
        rumbleCount += loopDelay;
        if(rumbleCount > 1000) {
            rumbleCount = 0;
            controller.rumble(".");
        }
        // firing logic with optical sensor
        if(states.cataStateIs(stateMachine::cata_state::PULLED_BACK)) {
            // closer to optical = higher proximity val; range from 0-255
            if(optical.get_proximity() > 250 ) { // && (optical.get_hue()) < 100 && optical.get_hue() > 80 
                // add delay
                states.setCataState(stateMachine::cata_state::FIRE);
            }
        }
    }
    // else {
    //     optical.set_led_pwm(0);
    // }

    // ******** DEBUG ******** //
    // if(displayInfo) {
    // // pros::screen::print(TEXT_MEDIUM_CENTER, 10, "Drive Velo: %d", (leftFrontDrive.get_actual_velocity() + rightFrontDrive.get_actual_velocity()) / 2);
    // // pros::screen::print(TEXT_MEDIUM_CENTER, 11, "Brake Ready?: %s", brakeReady ? "true" : "false");
    // pros::screen::print(TEXT_MEDIUM_CENTER, 5, "Puncher Enc: %d", cataEnc.get_position());
    // }
    pros::screen::print(TEXT_MEDIUM_CENTER, 4, "Cata Enc: %d", cataEnc.get_position());
    pros::screen::print(TEXT_MEDIUM_CENTER, 5, "Cata Angle: %d", cataEnc.get_angle());
    pros::screen::print(TEXT_MEDIUM_CENTER, 6, "Cata Current: %d", leftCata.get_current_draw() + rightCata.get_current_draw());
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "Opical prox: %d", optical.get_proximity());

    // Refresh display every 100 ms
    // displayCount += loopDelay;
    // if(displayCount > 100) {
    //     displayCount = 0;
    //     pros::screen::set_eraser(COLOR_BLACK);
    //     pros::screen::erase();
    // }

    // necessary task delay - do not change
    pros::delay(loopDelay); // while(pros::c::millis() < loopStartTime + loopDelay) {pros::delay(1);}
    }
}

// **** old matchload code ****//
    // while(matchloadState) {
    //     fireCount = 0;
    //     while(true) {
    //         // fire
    //         setCata(-127);

    //         // pull back
    //         while(cataEnc.get_position() < (FULL_PULLBACK_TICKS - 10000) && matchloadState) {pros::delay(5);}
    //         fireCount++;
    //         stopCata(pros::E_MOTOR_BRAKE_COAST);

    //         // optical sensor
    //         while(!(optical.get_proximity() < 150 && (optical.get_hue()) < 100 && optical.get_hue() > 80)){
    //             pros::delay(5);
    //         }

    //         if(!matchloadState) { // || fireCount >= fireTarget
    //             stopCata(pros::E_MOTOR_BRAKE_COAST);
    //             states.setCataState(stateMachine::cata_state::PULLED_BACK);
    //             // fireCount = fireTarget = 0;
    //             break;
    //         }
    //     }
    // }
    
    // while(matchloadState) {
    //     while(true) {
    //         setCata(-127);
    //         pros::delay(5);

    //         if(!matchloadState) {
    //             stopCata(pros::E_MOTOR_BRAKE_COAST);
    //             break;
    //         }
    //     }  
    // }