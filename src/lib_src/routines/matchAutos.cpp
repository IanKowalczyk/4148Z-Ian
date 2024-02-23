#include "lib_header/routines_h/matchAutos.h"

// ******** Current Autos ******** //
void defenseWP() { // descore matchload first, touches bar
	/**** mile gveore ****/
	// setup: top left corner of tile
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	states.setShooterState(stateMachine::shooter_state::FIRE);
	pros::delay(200);
	setMove(0, 260, 0, 120, 800);
	waitUntilSettled(0);
	setMove(0, 315, 0, 100, 500);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMove(0, 135, 0, 100, 800);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMove(36, 110, 80, 100, 1300);
	pros::delay(400);
	turn_target = 90;
	waitUntilSettled(0);
}

void defenseElims() { // mid rush and pull back both triballs
	// init
	globalPose.setPoint(40, 17, 1); // mirror of sixball

	// intake drop down
		states.setShooterState(stateMachine::shooter_state::FIRE);

	// 1: Rush mid triball
	setMoveToPoint(48, 62, 120, 120, 1000, false); // (48, 63)
		pros::delay(200);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(100);

	// 2: Scoop top triball over to our side
	setMove(-14.5, 280, 40, 120, 800); // move -15.5
        pros::delay(300);
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(0);
	setMove(0, 1, 0, 100, 600);
		pros::delay(200);
		max_turn_power = 60;
	waitUntilSettled(0);
	setMoveToPoint(50, 32, 100, 120, 800, true);
	waitUntilSettled(0);

	// 3: Push over both triballs
	setMove(12, 0, 500);
		pros::delay(300);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	setMove(-19, 90, 120, 95, 800);
	waitUntilSettled(0);
	setMove(0, 90, 0, 100, 500);
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    // setMoveToPoint(62, 38, 120, 100, 800, false);
	setMove(25, 90, 120, 100, 700);
	waitUntilSettled(0);
	setMove(-10, 90, 120, 100, 410);
	waitUntilSettled(0);
    // setMoveToPoint(62, 38, 120, 100, 800, false);
	setMove(15, 90, 120, 100, 700);
	waitUntilSettled(0);

	// 4: Back to matchload bar
	setMoveToPoint(42, 36, 600, true);
	waitUntilSettled(0);
	// setMoveToPoint(34, 12, 100, 120, 900, true); 
    setMoveToPoint(15.5, 27, 80, 120, 800, true); // (15.5, 27)
	waitUntilSettled(0);

    // 5: Descore matchload triball
    int descoreAngle = 131;
    setMove(0, descoreAngle, 0, 100, 500);
    waitUntilSettled(0);
        states.setWingState(stateMachine::wing_state::RIGHT_OUT);
        pros::delay(100);
    setMove(16, descoreAngle, 120, 100, 700);
    waitUntilSettled(200);
    setMove(0, 90, 0, 100, 500);
        pros::delay(300);
        states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    waitUntilSettled(0);
    setMove(0, descoreAngle, 0, 100, 500);
    waitUntilSettled(0);

	// 5: Push over alliance triball & hangbar triball
	setMoveToPoint(61, 11, 100, 120, 1000, false);
		// pros::delay(350);
		// max_translate_power = 120;
	waitUntilSettled(0);

	// 6: Final back to matchload bar, line up to bowl
	setMoveToPoint(27, 10, 1000, true);
	waitUntilSettled(0);
}

void sixBallWP() { // scores preload first, stable
	// init 
	// globalPose.setPoint(122, 16.4, 224); // old one where the matchload bar is pushed in
	globalPose.setPoint(121, 16.9, 225); // new setpoint where the matchload bar is as far out as possible
	
	// 1: Score preload
	setMove(-50, 210, 80, 80, 1000);
		pros::delay(400);
		turn_target = 185;
		max_turn_power = 100;
		pros::delay(100);
		max_drive_power = 100;
	waitUntilSettled(0);

	// 2: Line up to run 6 ball path
	setMoveToPoint(105, 32, 90, 120, 700, false);
		// drop intake
		setShooter(-120);
		pros::delay(300);
		max_translate_power = 120;
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	
	// 3: First half-ish of 6 ball path
	setMoveToPoint(77, 69, 90, 120, 1580, false); // (78, 67.5) confrimed working on real newSixBall
		pros::delay(300);
		max_translate_power = 125;
		setShooter(0);
	waitUntilSettled(100);
	setMove(0, 90, 0, 100, 600);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
		states.setIntakeState(stateMachine::intake_state::OFF);
	setMove(36, 92, 120, 80, 900);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		states.setIntakeState(stateMachine::intake_state::OFF);

	// 4: Grab third triball 
	setMoveToPoint(104, 52, 120, 120, 800, true);	// (104, 48)
	waitUntilSettled(0);
	setMove(0, 260, 0, 100, 410);
	waitUntilSettled(0);
	setMoveToPoint(82, 49, 700, false); // (82, 48)
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(100);

			// // 5: Score third triball
			// setMove(0, 70, 0, 100, 700);
			// waitUntilSettled(0);
			// setMoveToPoint(125, 64, 1000, false);
			// pros::delay(600);
			// 	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
			// waitUntilSettled(0);
			// 	states.setIntakeState(stateMachine::intake_state::OFF);

			// // 6: Back to start
			// setMoveToPoint(110, 14, 1000, true);
			// waitUntilSettled(0);

	/*** COPIED FROM NEWSIXBALL()*/
	// 3: Outtake third triball near matchload station
	setMove(0, 110, 0, 100, 500);
	waitUntilSettled(0);
	setMoveToPoint(103, 40, 120, 120, 600, false); // (106, 38) // 700
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);

	// 4: Swing and grab fourth triball
	setMoveToPoint(104, 19, 100, 120, 800, false); // (104, 14)
		states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	setMoveToPoint(74.7, 17, 60, 120, 940, false); // (75.5, 12)
		pros::delay(300);
		max_translate_power = 110;
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(150);

	// 4: Go back to matchload bar
	int descoreAngle = 50;
	setMoveToPoint(109, 22, 120, 125, 1100, true); // (109, 18)
	waitUntilSettled(0);
	setMove(0, 1, 0, 100, 600); // 45 deg
		pros::delay(200);
		turn_target = descoreAngle;
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::OFF);
	
	// 5: Descore matchload triball (fifth ball)
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	// setMoveToPoint(122, 23.5, 800, false); // (122, 23)
	setMove(19, descoreAngle, 800);
	waitUntilSettled(0);
	setMove(0, 15, 0, 100, 410);
		pros::delay(300); // 200 ms
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);

	// 6: Push triballs in from side of goal
	setMove(0, 80, 0, 100, 600); // 60 degrees
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::LEFT_OUT);
	setMove(28, 75, 120, 120, 1000);
		pros::delay(300); // 200ms
		turn_target = 0;
		max_drive_power = 0;
		pros::delay(250);
		max_drive_power = 125;
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);
	setMove(-15, 10, 120, 120, 600);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	// setMove(20, 10, 120, 120, 600);
	// waitUntilSettled(0);
	// setMove(-15, 0, 120, 120, 600);
	// 	states.setIntakeState(stateMachine::intake_state::OFF);
	// waitUntilSettled(0);
}

void sixBallElims() { // mid rush, guaranteed? 5 ball (maybe) hopefully
	// init
	globalPose.setPoint(103.5, 17, 1); // top left of tile

	// Wing push and intake drop down
		states.setShooterState(stateMachine::shooter_state::FIRE);
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		pros::delay(100);

	// 1: Rush mid triball
	setMoveToPoint(95, 63, 120, 120, 1000, false); // (94, 63)
		pros::delay(200);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(100);
	
	// 2: Back to start, outtake triball, grab hangbar triball
	setMoveToPoint(105, 14, 120, 120, 1000, true); 
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::OFF);
	setMove(0, 50, 0, 100, 410);
		pros::delay(280);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	setMoveToPoint(74, 13, 0, 125, 1000, false); // (75, 12)
		pros::delay(340);
		max_translate_power = 125;
	waitUntilSettled(100);
	
	// 3: Back to matchload bar
	int descoreAngle = 51;
	setMoveToPoint(109, 22, 120, 125, 1100, true); // (109, 18)
	waitUntilSettled(0);
	setMove(0, 330, 0, 100, 500); 
		pros::delay(200);
		turn_target = descoreAngle;
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::OFF);

	// 4: Descore matchload triball
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	setMove(19, descoreAngle, 120, 100, 400); // 400 ms
	waitUntilSettled(0);
	setMove(0, 15, 0, 120, 410);
		pros::delay(300); // 200 ms
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	
	// 5: Score first four triballs from side of goal
	setMove(0, 80, 0, 120, 450);
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::LEFT_OUT);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMove(28, 70, 120, 120, 1000);
		pros::delay(250); // 200ms
		turn_target = 0;
		max_drive_power = 40;
		pros::delay(150); // 200 ms
		max_drive_power = 125;
		pros::delay(200);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	// second push - please be in time please
	// setDrive(-127, -127);
	// pros::delay(200);
	// setDrive(127, 127);
	// pros::delay(400);

	// 6: Get fifth triball (triball on bar at 72, 48)
	setMoveToPoint(98, 51, 100, 100, 1000, true); // (98, 47)
		pros::delay(150);
		max_rotate_power = 125;
		states.setIntakeState(stateMachine::intake_state::INTAKING);
		pros::delay(300);
		max_translate_power = 125;
	waitUntilSettled(0);
	setMoveToPoint(78, 50, 0, 125, 1000, false); // (79, 47)
		pros::delay(300);
		max_translate_power = 125;
	waitUntilSettled(100);

	// 7: Score fifth triball
	setMoveToPoint(125, 72, 0, 120, 1000, false); // (125, 70)
		pros::delay(350);
		max_translate_power = 120;
		max_rotate_power = 100;
		pros::delay(200);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);

	// 8: Grab last triball
	setMoveToPoint(90, 56, 120, 120, 700, true);
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	setMoveToPoint(77, 80, 0, 125, 900, false); // triball 6 // (77, 74)
		pros::delay(300);
		max_translate_power = 125;
	waitUntilSettled(0);

	// 9: Score last triball
	setMove(0, 90, 0, 120, 500);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
	setMove(36, 92, 125, 80, 850); // relative goal push instead of moveToPoint
	// setMoveToPoint(125, 75, 120, 120, 900, false); // absolute goal push
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		states.setIntakeState(stateMachine::intake_state::OFF);
	setMove(-8, 90, 500);
	waitUntilSettled(0);
}


// ******** Old Autos ******** //
void defenseAuto(defense_auto_mode s) {
	// **** Setup **** //
	globalPose.setPoint(48 - BASE_X_OFFSET, 24 - BASE_Y_OFFSET, 0); // top right of tile

	// Drop intake by firing shooter
	states.setShooterState(stateMachine::shooter_state::FIRE);
	
	// 1: RUSH MID TRIBALL
	setMoveToPoint(48, 62, 120, 120, 1100, false);
	// pros::delay(400);
	// max_translate_power = 120;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(100);


	if(s == defense_auto_mode::FOUR_BALL) {
		setMove(-8, 0, 600);
		waitUntilSettled(0);
		// 2: TURN AND SCOOP 2ND TRIBALL
		setMoveToPoint(58, 58, 0, 100, 1000, true);
		pros::delay(500);
		max_translate_power = 100;
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		waitUntilSettled(0);
		setMove(0, 45, 0, 100, 800);
		waitUntilSettled(200);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	}

	// 3: BACK TO BAR
	setMoveToPoint(20, 24, 120, 120, 1300, true);
	waitUntilSettled(0);

	// 4: DESCORE
	setMove(0, 130, 0, 100, 800);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	pros::delay(300);
	setMove(0, 90, 0, 100, 800);
	waitUntilSettled(0);
	setMove(0, 135, 0, 100, 800);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);

	// 5: TOUCH HANG BAR
	// states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	// setShooter(-65);
	// pros::delay(200);
	// setShooter(0);
	// setMoveToPoint(38, 9, 0, 100, 1100, true);
	// pros::delay(500);
	// max_translate_power = 100;
	// states.setIntakeState(stateMachine::intake_state::OFF);
	// waitUntilSettled(0);
	// setMoveToPoint(66.5, 10, 80, 100, 1300, true);
	// waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMove(43, 110, 80, 100, 1400);
	pros::delay(400);
	turn_target = 90;
	waitUntilSettled(0);	

	// setMoveToPoint(65, 10, 1000, false);
	// waitUntilSettled(0);
	// setDrive(30, -30);
	// pros::delay(500);
	// states.setIntakeState(stateMachine::intake_state::OFF);

	// // 1: Flick preload and rush mid
	// states.setWingState(stateMachine::wing_state::LEFT_OUT);
	// pros::delay(200);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// // TODO: intake ball or push with wings instead???
	// setMoveToPoint(48, 63, 100, 120, 1700, false);
	// pros::delay(400);
	// states.setIntakeState(stateMachine::intake_state::INTAKING);
	// max_translate_power = 110;
	// waitUntilSettled(0);
	// setMove(-10, 0, 800);
	// waitUntilSettled(0);

	// // 2: Go back to goal and push preload in
	// setMoveToPoint(48, 40, 1300, true);
	// waitUntilSettled(0);
	// setMoveToPoint(14, 30, 60, 120, 1200, true);
	// pros::delay(300);
	// max_translate_power = 120;
	// waitUntilSettled(0);
	// // push in
	// setMoveToPoint(12, 52, 10, 120, 1200, true);
	// pros::delay(400);
	// max_translate_power = 120;
	// waitUntilSettled(0);

	// // 3: Descore matchload triball and touch hangbar with intake
	// // setMoveToPoint()
	// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
}

void offenseAuto(offense_auto_mode s) {
	globalPose.setPoint(32, 14, 0);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(100);

	setMoveToPoint(43, 64, 1500, false);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);

	setMoveToPoint(62, 65, 1500, false);
	waitUntilSettled(0);

	setMoveToPoint(23, 23, 1500, false);
	waitUntilSettled(0);

	setMoveToPoint(13, 40, 1500, false);
	waitUntilSettled(0);

	setMoveToPoint(26, 16, 1500, false);
	waitUntilSettled(0);

	setMoveToPoint(66, 13, 1500, false);
	waitUntilSettled(0);
	
}

void newSixBall(sixBall_mode s) { // GOOD
	globalPose.setPoint(103.5, 17, 1); // top left of tile
	// states.setShooterState(stateMachine::shooter_state::PULLED_BACK);

	// Wing push and intake drop down
	states.setShooterState(stateMachine::shooter_state::FIRE);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);

	// **** Rush mid **** //
	if(s == sixBall_mode::BAR) {
			setMoveToPoint(80, 63, 80, 100, 1450, false); // (80, 64)
			pros::delay(300);
			max_translate_power = 120;
			
		// setMoveToPoint(80, 64, 120, 80, 1450, false); // (80, 62)
	}
	if(s == sixBall_mode::MID) {
		setMoveToPoint(94, 63, 120, 100, 1000, false);
	}

		pros::delay(200);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	pros::delay(100);

	// 1,2: Score first two mid triballs 
	if(s == sixBall_mode::MID) {
		setMove(-8, 0, 500);
		waitUntilSettled(0);
		setMove(0, 80, 0, 120, 500);
		waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		setMoveToPoint(125, 60, 700, false);
		waitUntilSettled(0);
		setMoveToPoint(88, 57, 700, true);
		waitUntilSettled(0);
		setMoveToPoint(80, 63, 0, 100, 800, false); // (82, 72)
		pros::delay(500);
		max_translate_power = 100;
		states.setIntakeState(stateMachine::intake_state::INTAKING);
		waitUntilSettled(0);
	}
	// if(s == sixBall_mode::BAR) {
		setMove(0, 90, 0, 100, 600, false);
		waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
		states.setIntakeState(stateMachine::intake_state::OFF);
		setMove(36, 92, 120, 100, 900);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		states.setIntakeState(stateMachine::intake_state::OFF);
	// }


	// 3: Grab third triball 
	setMoveToPoint(104, 48, 120, 120, 900, true);
	waitUntilSettled(0);
	setMove(0, 260, 0, 100, 410);
	waitUntilSettled(0);
	setMoveToPoint(82, 48, 750, false); // (82, 45) // 800
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);

	// 3: Outtake third triball near matchload station
	setMove(0, 110, 0, 100, 600);
	waitUntilSettled(0);
	setMoveToPoint(103, 38, 120, 120, 600, false); // (106, 36) // 700
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);

	// 4: Swing and grab fourth triball
	setMoveToPoint(104, 14, 100, 120, 800, false); // (110, 15)
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	setMoveToPoint(75.5, 12, 60, 120, 920, false); // (74, 12)
	pros::delay(300);
	max_translate_power = 110;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	pros::delay(150);

	// 4: Go back to matchload bar
	setMoveToPoint(109, 18, 120, 120, 1200, true); // (110, 15)
	pros::delay(500);
	waitUntilSettled(100);
	setMove(0, 45, 0, 100, 700);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OFF);
	
	// 5: Descore matchload triball (fifth ball)
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	setMoveToPoint(122, 23, 800, false); // (123, 24) // (120, 22)
	waitUntilSettled(0);
	setMove(0, 15, 0, 100, 400);
	pros::delay(200);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);

	// 6: Push triballs in from side of goal
	setMove(0, 75, 0, 100, 600); // 60 degrees
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	setMove(28, 50, 120, 120, 900);
	pros::delay(300); // 200ms
	turn_target = 0;
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMove(-15, 10, 120, 120, 600);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMove(20, 10, 120, 120, 600);
	waitUntilSettled(0);
	setMove(-15, 0, 120, 120, 600);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
}

void fourBall() {
	globalPose.setPoint(120 - BASE_X_OFFSET, 24 - BASE_Y_OFFSET, 0);

	// 1: Turn and descore matchload 
	setMove(0, 45, 0, 100, 800);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	pros::delay(200);
	setMove(18, 45, 1000);
	waitUntilSettled(0);
	// turn to descore
	setMove(0, 15, 0, 100, 500);
	pros::delay(200);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);

	// 2: Push triballs in from side of goal
	setMove(0, 60, 0, 100, 600);
	states.setShooterState(stateMachine::shooter_state::FIRE);
	waitUntilSettled(0);
	setMove(28, 50, 120, 120, 900);
	pros::delay(200);
	turn_target = 0;
	waitUntilSettled(0);
	setMove(-8, 0, 120, 120, 600);
	waitUntilSettled(0);
	// setMove(20, 10, 120, 120, 600);
	// waitUntilSettled(0);
	// setMove(-10, 0, 120, 120, 600);
	// waitUntilSettled(0);
}


// ******** ARCHIVE ******** //

// void defenseWP { // OLD DEFENSE WP 
	// globalPose.setPoint(24, 24 - BASE_Y_OFFSET, 180);
	// // 1: Push first triball in
	// setMove(-30, 140, 80, 100, 1500);
	// pros::delay(400);
	// turn_target = 180;
	// max_drive_power = 120;
	// waitUntilSettled(0);
	// // 2: Descore matchload
	// setMoveToPoint(22, 12, 1000, false); // (24, 12)
	// pros::delay(300);
	// states.setWingState(stateMachine::wing_state::WINGS_OUT);
	// waitUntilSettled(0);
	// setMove(0, 100, 0, 100, 700);
	// waitUntilSettled(0);
	// setMove(0, 135, 0, 100, 800);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// waitUntilSettled(0);
	// // 3: Touch hangbar
	// setMoveToPoint(73 - TOTAL_Y_OFFSET, 12, 110, 120, 1300, false);
	// states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	// waitUntilSettled(0);
	// states.setIntakeState(stateMachine::intake_state::OFF);
	// states.setShooterState(stateMachine::shooter_state::FIRE);
    // }

// void newSixBall(sixBall_mode s) { // STABLE
    // 	globalPose.setPoint(103.5, 17, 1); // top left of tile
    // 	// states.setShooterState(stateMachine::shooter_state::PULLED_BACK);

    // 	// Wing push and intake drop down
    // 	states.setShooterState(stateMachine::shooter_state::FIRE);
    // 	states.setWingState(stateMachine::wing_state::RIGHT_OUT);

    // 	// **** Rush mid **** //
    // 	if(s == sixBall_mode::BAR) {
    // 			setMoveToPoint(80, 63, 80, 100, 1450, false); // (80, 64)
    // 			pros::delay(300);
    // 			max_translate_power = 120;
                
    // 		// setMoveToPoint(80, 64, 120, 80, 1450, false); // (80, 62)
    // 		pros::delay(200);
    // 		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    // 	}
    // 	if(s == sixBall_mode::MID) {
    // 		setMoveToPoint(94, 64, 120, 100, 1700, false);
    // 	}

    // 	pros::delay(500);
    // 	// stopShooter(pros::E_MOTOR_BRAKE_COAST);
    // 	states.setIntakeState(stateMachine::intake_state::INTAKING);
    // 	waitUntilSettled(0);
    // 	pros::delay(100);

    // 	// 1,2: Score first two mid triballs 
    // 	// if(s == sixBall_mode::BAR) {
    // 	// 	setMove(-5, 315, 120, 100, 500);
    // 	// 	waitUntilSettled(0);
    // 	// }
    // 	setMove(0, 90, 0, 100, 700, false);
    // 	waitUntilSettled(0);
    // 	if(s == sixBall_mode::BAR) {
    // 		states.setWingState(stateMachine::wing_state::WINGS_OUT);
    // 		states.setIntakeState(stateMachine::intake_state::OFF);
    // 	}
    // 	setMove(36, 92, 100, 80, 1000);
    // 	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    // 	waitUntilSettled(0);
    // 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    // 	states.setIntakeState(stateMachine::intake_state::OFF);
        
    // 	// 3: Grab third triball 
    // 	setMoveToPoint(104, 48, 120, 120, 900, true);
    // 	waitUntilSettled(0);
    // 	setMove(0, 260, 0, 100, 400);
    // 	waitUntilSettled(0);
    // 	setMoveToPoint(82, 48, 750, false); // (82, 45) // 800
    // 	states.setIntakeState(stateMachine::intake_state::INTAKING);
    // 	pros::delay(100);
    // 	waitUntilSettled(0);

    // 	// 3: Outtake third triball near matchload station
    // 	setMove(0, 110, 0, 100, 700);
    // 	waitUntilSettled(0);
    // 	setMoveToPoint(103, 38, 120, 120, 600, false); // (106, 36) // 700
    // 	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    // 	waitUntilSettled(0);

    // 	// 4: Swing and grab fourth triball
    // 	setMoveToPoint(104, 14, 100, 120, 800, false); // (110, 15)
    // 	states.setIntakeState(stateMachine::intake_state::OFF);
    // 	waitUntilSettled(0);
    // 	setMoveToPoint(74, 12, 60, 120, 900, false); // (75.5, 12)
    // 	pros::delay(300);
    // 	max_translate_power = 110;
    // 	states.setIntakeState(stateMachine::intake_state::INTAKING);
    // 	waitUntilSettled(0);
    // 	pros::delay(150);

    // 	// 4: Go back to matchload bar
    // 	setMoveToPoint(109, 18, 120, 120, 1200, true); // (110, 15)
    // 	pros::delay(500);
    // 	waitUntilSettled(100);
    // 	setMove(0, 45, 0, 100, 700);
    // 	waitUntilSettled(0);
    // 	states.setIntakeState(stateMachine::intake_state::OFF);
        
    // 	// 5: Descore matchload triball (fifth ball)
    // 	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
    // 	setMoveToPoint(120, 24, 800, false); // (123, 24) // new: 120, 22
    // 	waitUntilSettled(0);
    // 	setMove(0, 15, 0, 100, 400);
    // 	pros::delay(200);
    // 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    // 	// states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    // 	waitUntilSettled(0);

    // 	// 6: Push triballs in from side of goal
    // 	setMove(0, 75, 0, 100, 600); // 60 degrees
    // 	states.setWingState(stateMachine::wing_state::WINGS_OUT);
    // 	waitUntilSettled(0);
    // 	states.setWingState(stateMachine::wing_state::LEFT_OUT);
    // 	setMove(28, 50, 120, 120, 900);
    // 	pros::delay(300); // 200ms
    // 	turn_target = 0;
    // 	waitUntilSettled(0);
    // 	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    // 	setMove(-15, 10, 120, 120, 600);
    // 	waitUntilSettled(0);
    // 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    // 	setMove(20, 10, 120, 120, 600);
    // 	waitUntilSettled(0);
    // 	setMove(-15, 0, 120, 120, 600);
    // 	states.setIntakeState(stateMachine::intake_state::OFF);
    // 	waitUntilSettled(0);
    // }


// void oldSixBall(sixBall_mode s) {
    // 	// globalPose.setPoint(96 + 16, 17, 0); // right drive c-channel in line with left edge of tile, front aligned to top edge of tile
    // 	// globalPose.setPoint(118, 13, 325); // angled to face triball near bar
    // 	globalPose.setPoint(120, 14, 321); // angled to face triball near bar; right front wheel in line with intersection of tiles; (24, 14)

    // 	// Wing push and intake drop down // very old
    // 	// states.setShooterState(stateMachine::Shooter_state::FIRE);
    // 	// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
    // 	// pros::delay(200);
    // 	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);

    // 	// shimmy to drop intake // old
    // 	// setDrive(120, 120);
    // 	// pros::delay(100);
    // 	// setDrive(-120, -120);
    // 	// pros::delay(200);
    // 	// stopDrive(pros::E_MOTOR_BRAKE_COAST);

    // 	/** Drop intake */
    // 	states.setShooterState(stateMachine::shooter_state::FIRE);

    // 	// **** Rush mid **** //
    // 	if(s == sixBall_mode::BAR) {
    // 			// setMoveToPoint(85, 62, 120, 120, 1650, false); // (85, 62)
    // 			// pros::delay(460);
    // 			// max_translate_power = 120;
    // 		setMoveToPoint(80, 60, 120, 120, 1550, false); // (85, 62) // 2: (80, 60)
    // 	}
    // 	if(s == sixBall_mode::MID) {
    // 		setMoveToPoint(94, 64, 120, 100, 1700, false);
    // 	}

    // 	pros::delay(500);
    // 	states.setIntakeState(stateMachine::intake_state::INTAKING);
    // 	waitUntilSettled(0);
    // 	pros::delay(100);

    // 	// 1,2: Score first two mid triballs 
    // 	// if(s == sixBall_mode::BAR) {
    // 	// 	setMove(-5, 315, 120, 100, 500);
    // 	// 	waitUntilSettled(0);
    // 	// }
    // 	setMove(0, 90, 0, 100, 700, false);
    // 	waitUntilSettled(0);
    // 	if(s == sixBall_mode::BAR) {
    // 		states.setWingState(stateMachine::wing_state::WINGS_OUT);
    // 		states.setIntakeState(stateMachine::intake_state::OFF);
    // 	}
    // 	setMoveToPoint(117, 63, 120, 120, 1000, false); // (118, 70)
    // 	waitUntilSettled(0);
    // 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
        
    // 	// 3: Grab third triball 
    // 	// setMoveToPoint(82, 42, 80, 120, 1500, true); // (85, 48)
    // 	// waitUntilNear(30, 0);
    // 	// movement_reversed = false;
    // 	// max_translate_power = 0;
    // 	// pros::delay(600);
    // 	// max_translate_power = 100;
    // 	// states.setIntakeState(stateMachine::intake_state::INTAKING);
    // 	// waitUntilSettled(0);
    // 	setMoveToPoint(104, 48, 120, 120, 900, true);
    // 	waitUntilSettled(0);
    // 	setMove(0, 260, 0, 100, 660);
    // 	waitUntilSettled(0);
    // 	setMoveToPoint(82, 45, 800, false); // (82, 48)
    // 	states.setIntakeState(stateMachine::intake_state::INTAKING);
    // 	waitUntilSettled(0);

    // 	// 3: Outtake third triball near matchload station
    // 	setMove(0, 110, 0, 100, 700);
    // 	states.setIntakeState(stateMachine::intake_state::OFF);
    // 	waitUntilSettled(0);
    // 	setMoveToPoint(106, 36, 120, 120, 700, false); // (108, 36) // 2200 
    // 	pros::delay(100);
    // 	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
    // 	waitUntilSettled(0);

    // 	// 4: Swing and grab fourth triball
    // 	setMoveToPoint(110, 14, 100, 120, 800, false); // (110, 15)
    // 	states.setIntakeState(stateMachine::intake_state::OFF);
    // 	// waitUntilNear(2.5, 0);
    // 	waitUntilSettled(0);
    // 	setMoveToPoint(81, 9, 110, 120, 780, false); // (80.5, 12) // (72 + BASE_Y_OFFSET, 9)
    // 	pros::delay(300);
    // 	states.setIntakeState(stateMachine::intake_state::INTAKING);
    // 	waitUntilSettled(0);
    // 	pros::delay(150);

    // 	// 4: Go back to matchload bar
    // 	setMoveToPoint(109, 15, 120, 120, 1200, true); // (110, 15)
    // 	pros::delay(500);
    // 	states.setIntakeState(stateMachine::intake_state::OFF);
    // 	waitUntilSettled(100);
    // 	setMove(0, 45, 0, 100, 700);
    // 	waitUntilSettled(0);
        
    // 	// 5: Descore matchload triball (fifth ball)
    // 	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
    // 	setMoveToPoint(123.2, 24, 1000, false); // (123, 24)
    // 	waitUntilSettled(0);
    // 	setMove(0, 15, 0, 100, 400);
    // 	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    // 	waitUntilSettled(0);

    // 	// 6: Push triballs in from side of goal
    // 	setMove(0, 60, 0, 100, 600);
    // 	// states.setWingState(stateMachine::wing_state::WINGS_OUT);
    // 	waitUntilSettled(0);
    // 	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
    // 	setMove(28, 50, 120, 120, 900);
    // 	pros::delay(200);
    // 	turn_target = 0;
    // 	waitUntilSettled(0);
    // 	setMove(-8, 0, 120, 120, 600);
    // 	waitUntilSettled(0);
    // 	setMove(20, 10, 120, 120, 600);
    // 	waitUntilSettled(0);
    // 	setMove(-10, 0, 120, 120, 600);
    // 	waitUntilSettled(0);
    // }