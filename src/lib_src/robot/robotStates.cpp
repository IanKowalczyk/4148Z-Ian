#include "lib_header/robot_h/robotStates.h"

stateMachine states;
bool runStateHandler = false;

void stateHandler() {
    // default states
    matchloadState = false;
    states.setIntakeState(stateMachine::intake_state::OFF);
    states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    states.setParkingBrakeState(stateMachine::parking_brake_state::BRAKE_OFF);
    states.setShooterState(stateMachine::shooter_state::PULLED_BACK);

    // set sensor data rates
    inertial.set_data_rate(5);
    frontEnc.set_data_rate(5);
    sideEnc.set_data_rate(5);
    shooterEnc.set_data_rate(5);

    // default brake modes
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    setShooterBrakeMode(pros::E_MOTOR_BRAKE_COAST);

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

    // matchload first loop
    bool matchloadFirstLoop = false;

    // signal stateHanlder is running
    controller.rumble("-");

    while(true) {
    // int loopStartTime = pros::c::millis();

     // ******** Odometry ******** //
    // if(pros::competition::is_autonomous()) {
        updatePosition();
    // }

    // ******** Intake state handler ******** //
    if(states.intakeStateChanged()) {
        if(states.intakeStateIs(stateMachine::intake_state::OFF)) {
            intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            intake.brake();
            intakeCount = 0;
        }
        else if(states.intakeStateIs(stateMachine::intake_state::INTAKING)) {
            intake.move(127);
        }
        else if(states.intakeStateIs(stateMachine::intake_state::OUTTAKING)) {
            intake.move(-127);
        }
        states.oldIntakeState = states.intakeState;
    }

    // If triball in intake, rumble controller
    if(states.intakeStateIs(stateMachine::intake_state::INTAKING)) {
        intakeCount += loopDelay;
        if(intakeCount > 200 && intake.get_current_draw() > 1500) {
            controller.rumble("-");
        }
    }
    else {intakeCount = 0;}

    // TODO - Better firing logic (e.g. fire, wait until sensor jumps back to zero-ish, then pull back)
    // ******** Shooter state handler ******** // 
    if(states.shooterStateChanged()) {
        if(states.shooterStateIs(stateMachine::shooter_state::FIRE)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "SHOOTER FIRED");}
            setShooter(-127);
            fireCount += loopDelay;
            if(fireCount > MIN_FIRE_TIME) {
                fireCount = 0;
                states.setShooterState(stateMachine::shooter_state::SHORT_PULLBACK);
            }
        }

        if(states.shooterStateIs(stateMachine::shooter_state::SHORT_PULLBACK)) {
            // if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 2, "SHORT PULLBACK, Volt: %d", cataMotors.get_voltages());}
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "PULLING BACK");}
            setShooter(-127);
            if(shooterEnc.get_position() > (SHORT_PULLBACK_TICKS - PULLBACK_THRESHOLD) || pullbackCount >= PULLBACK_TIMEOUT) {
                stopShooter(pros::E_MOTOR_BRAKE_COAST);
                states.setShooterState(stateMachine::shooter_state::PULLED_BACK);
            }
            pullbackCount += loopDelay;
        }

        if(states.shooterStateIs(stateMachine::shooter_state::PULLED_BACK)) {
            if(displayInfo) {pros::screen::print(TEXT_MEDIUM_CENTER, 3, "PULLED BACK !!!!!!!");}
            // stopCata(pros::E_MOTOR_BRAKE_COAST);
            pullbackCount = 0;
            states.oldShooterState = states.shooterState;
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
        matchloadFirstLoop = true;
        optical.set_led_pwm(100);
        // rumble every second to signal we are in matchload state
        rumbleCount += loopDelay;
        if(rumbleCount > 1000) {
            rumbleCount = 0;
            controller.rumble(".");
        }
        // firing logic with optical sensor
        if(states.shooterStateIs(stateMachine::shooter_state::PULLED_BACK)) {
            // closer to optical = higher proximity val; range from 0-255
            if(optical.get_proximity() > 250 ) { // && (optical.get_hue()) < 100 && optical.get_hue() > 80 
                // add delay
                pros::delay(100);
                states.setShooterState(stateMachine::shooter_state::FIRE);
                triballsFired++;
            }
        }
    }
    else {
        if(matchloadFirstLoop) {
            optical.set_led_pwm(0);
            triballsFired = 0;
            matchloadFirstLoop = false;
        }
    }

    // ******** DEBUG ******** //
    if(displayInfo) {
    // // pros::screen::print(TEXT_MEDIUM_CENTER, 10, "Drive Velo: %d", (leftFrontDrive.get_actual_velocity() + rightFrontDrive.get_actual_velocity()) / 2);
    // // pros::screen::print(TEXT_MEDIUM_CENTER, 11, "Brake Ready?: %s", brakeReady ? "true" : "false");
    // pros::screen::print(TEXT_MEDIUM_CENTER, 5, "Puncher Enc: %d", cataEnc.get_position());

    // new stuff
    pros::screen::print(TEXT_MEDIUM_CENTER, 4, "Shooter Enc: %d", shooterEnc.get_position());
    pros::screen::print(TEXT_MEDIUM_CENTER, 5, "Shooter Angle: %d", shooterEnc.get_angle());
    pros::screen::print(TEXT_MEDIUM_CENTER, 6, "Shooter Current: %d", leftShooter.get_current_draw() + rightShooter.get_current_draw());
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "Opical prox: %d", optical.get_proximity());
    }
    pros::screen::erase_line(0, 3, 800, 3);
    pros::screen::print(TEXT_MEDIUM, 3, "Shooter Enc: %5d, Ang: %5d | Prox: %d", shooterEnc.get_position(), shooterEnc.get_angle(), optical.get_proximity());
    // pros::screen::erase_line(0, 4, 600, 5);
    // pros::screen::print(TEXT_MEDIUM, 4, "Front Enc rotation: %d", frontEnc.get_position());

    // pros::screen::print(TEXT_MEDIUM, 5, "Opical prox: %d", optical.get_proximity());

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