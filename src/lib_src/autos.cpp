#include "lib_header/autos.h"

// ******** Setpoints ******** //
Point leftTriball1(48, 72);		// Left mid - auto line (48, 72)
Point leftTriball2(68, 72);		// Left pole - auto line (68, 72)
Point rightTriball3(76, 72);	// Right pole - auto line (76, 72)
Point rightTriball4(96, 72);	// Right mid - auto line (96, 72)
Point rightTriball5(76, 48);	// Right pole, in line with goal post (76, 48)
Point hangBarTriball(72, 12);	// Underneath hang bar (72, 12)

Point leftBottomMatchload(20, 20);		// In front of left bottom matchload station (20, 20)
Point rightBottomMatchload(124, 20);	// In front of right bottom matchload station (124, 20)
Point leftTopMatchload(20, 124);		// In front of left top matchload station (20, 124)
Point rightTopMatchload(124, 124);		// In front of right top matchload  (124, 124)

// ******** Test Autos ******** //
void autoFunctionTest() {
	// Intake
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(300);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	pros::delay(300);
	states.setIntakeState(stateMachine::intake_state::OFF);
	pros::delay(500);

	// Wing
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(250);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	pros::delay(250);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(250);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	pros::delay(500);

	// Shooter
	states.setShooterState(stateMachine::shooter_state::FIRE);
	pros::delay(500);

	// Matchload
	matchloadState = true;
	pros::delay(2000);
	matchloadState = false;

	// 
}

void odomBoxTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(0, 24, 1200, false);
    waitUntilSettled(0);
    setMoveToPoint(24, 24, 1200, false);
    waitUntilSettled(0);
    setMoveToPoint(24, 0, 1200, false);
    waitUntilSettled(0);
    setMoveToPoint(0, 0, 1200, false);
    waitUntilSettled(500);
}

void odomTriangleTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(20, 20, 1500, false);
	waitUntilSettled(0);
	setMoveToPoint(40, 0, 1500, false);
	waitUntilSettled(0);
	setMoveToPoint(0, 0, 1500, false);
	waitUntilSettled(500);
}

void squigglesTest() {
    globalPose.setPoint(0.0, 0.0, 0);	// Initialize position
    setMove(20, 30, 100, 80, 2000);		// right curve
	pros::delay(500);
	setMove(20, 330, 100, 80, 2000);	// left curve
	pros::delay(500);
	setMove(10, 45, 100, 80, 2000);		// small right curve
	pros::delay(500);
	setMove(8, 0, 100, 80, 1000);		// straight
	waitUntilSettled(0);
	setMoveToPoint(0, 0, 1500, false);	// back to origin
	waitUntilSettled(500);
}

void chainedMoveToPoint() {
	// Test: chaining together moveToPoints to run a path
    setMoveToPoint(40, 36, 1200, false);
	pros::delay(800);
	setMoveToPoint(40, 0, 1200, false);
	pros::delay(800);
	setMoveToPoint(0, 0, 1200, false);
	waitUntilSettled(500);
}

void oldCurveTest() {
	// OLD CURVE LOGIC
	setMove(10000, 0, 127, 80, 5000);
	for(int i = 0; i < (360/10) ; i++) {
		turn_target += 10;
		pros::delay(100);
	}
	waitUntilSettled(20);
}
void curveTuning() {
	// CURVE TUNING
	setCurve(30, -180, 6, 100, 100, 5000); // curve direction depends on sign of endangle
	waitUntilSettled(20);
	setCurve(30, 0, 6, 100, 100, 3000);
	waitUntilSettled(20);
	pros::delay(1000);
}

// **** Autos **** //
void defenseAuto(defense_auto_mode s) {
	// **** Setup **** //
	// left base with outer edge of tile; front of drive with top edge of tile
	globalPose.setPoint(24 + BASE_X_OFFSET, 24 - BASE_Y_OFFSET, 0);

	// 1: Flick preload and rush mid 
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(200);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// TODO: intake ball or push with wings instead???
	setMoveToPoint(48, 63, 100, 120, 1700, false);
	pros::delay(400);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	max_translate_power = 110;
	waitUntilSettled(0);
	setMove(-10, 0, 800);
	waitUntilSettled(0);

	// 2: Go back to goal and push preload in
	setMoveToPoint(48, 40, 1300, true);
	waitUntilSettled(0);
	setMoveToPoint(14, 30, 60, 120, 1200, true);
	pros::delay(300);
	max_translate_power = 120;
	waitUntilSettled(0);
	// push in
	setMoveToPoint(12, 52, 10, 120, 1200, true);
	pros::delay(400);
	max_translate_power = 120;
	waitUntilSettled(0);

	// 3: Descore matchload triball and touch hangbar with intake
	// setMoveToPoint()
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
}

void defenseSafe() {
	globalPose.setPoint(24, 24 - BASE_Y_OFFSET, 180);

	// 1: Push first triball in
	setMove(-30, 140, 80, 100, 1500);
	pros::delay(400);
	turn_target = 180;
	max_drive_power = 120;
	waitUntilSettled(0);

	// 2: Descore matchload
	setMoveToPoint(22, 12, 1000, false); // (24, 12)
	pros::delay(300);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
	setMove(0, 100, 0, 100, 700);
	waitUntilSettled(0);
	setMove(0, 135, 0, 100, 800);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);

	// 3: Touch hangbar
	setMoveToPoint(73 - TOTAL_Y_OFFSET, 12, 110, 120, 1300, false);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OFF);
	states.setShooterState(stateMachine::shooter_state::FIRE);
}

void offenseAuto(offense_auto_mode s) {

}

void sixBall(sixBall_mode s) {
	// globalPose.setPoint(96 + 16, 17, 0); // right drive c-channel in line with left edge of tile, front aligned to top edge of tile
	// globalPose.setPoint(118, 13, 325); // angled to face triball near bar
	globalPose.setPoint(120, 14, 321); // angled to face triball near bar; right front wheel in line with intersection of tiles; (24, 14)

	// Wing push and intake drop down
	// states.setShooterState(stateMachine::Shooter_state::FIRE);
	// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	// pros::delay(200);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	setDrive(120, 120);
	pros::delay(100);
	setDrive(-120, -120);
	pros::delay(200);
	stopDrive(pros::E_MOTOR_BRAKE_COAST);

	// **** Rush mid **** //
	if(s == sixBall_mode::BAR) {
			// setMoveToPoint(85, 62, 120, 120, 1650, false); // (85, 62)
			// pros::delay(460);
			// max_translate_power = 120;
		setMoveToPoint(80, 60, 120, 120, 1550, false); // (85, 62) // 2: (80, 60)
	}
	if(s == sixBall_mode::MID) {
		setMoveToPoint(94, 64, 120, 100, 1700, false);
	}

	pros::delay(800);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	pros::delay(100);

	// 1,2: Score first two mid triballs 
	// if(s == sixBall_mode::BAR) {
	// 	setMove(-5, 315, 120, 100, 500);
	// 	waitUntilSettled(0);
	// }
	setMove(0, 90, 0, 100, 700, false);
	waitUntilSettled(0);
	if(s == sixBall_mode::BAR) {
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
		states.setIntakeState(stateMachine::intake_state::OFF);
	}
	setMoveToPoint(117, 63, 120, 120, 1000, false); // (118, 70)
	states.setShooterState(stateMachine::shooter_state::FIRE);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	
	// 3: Grab third triball 
	// setMoveToPoint(82, 42, 80, 120, 1500, true); // (85, 48)
	// waitUntilNear(30, 0);
	// movement_reversed = false;
	// max_translate_power = 0;
	// pros::delay(600);
	// max_translate_power = 100;
	// states.setIntakeState(stateMachine::intake_state::INTAKING);
	// waitUntilSettled(0);
	setMoveToPoint(104, 48, 120, 120, 900, true);
	waitUntilSettled(0);
	setMove(0, 260, 0, 100, 660);
	waitUntilSettled(0);
	setMoveToPoint(82, 45, 800, false); // (82, 48)
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);

	// 3: Outtake third triball near matchload station
	setMove(0, 110, 0, 100, 700);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	setMoveToPoint(106, 36, 120, 120, 700, false); // (108, 36) // 2200 
	pros::delay(100);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);

	// 4: Swing and grab fourth triball
	setMoveToPoint(110, 14, 100, 120, 800, false); // (110, 15)
	states.setIntakeState(stateMachine::intake_state::OFF);
	// waitUntilNear(2.5, 0);
	waitUntilSettled(0);
	setMoveToPoint(81, 9, 110, 120, 780, false); // (80.5, 12) // (72 + BASE_Y_OFFSET, 9)
	pros::delay(300);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	pros::delay(150);

	// 4: Go back to matchload bar
	setMoveToPoint(109, 15, 120, 120, 1200, true); // (110, 15)
	pros::delay(500);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(100);
	setMove(0, 45, 0, 100, 700);
	waitUntilSettled(0);
	
	// 5: Descore matchload triball (fifth ball)
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	setMoveToPoint(123.2, 24, 1000, false); // (123, 24)
	waitUntilSettled(0);
	setMove(0, 15, 0, 100, 400);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);

	// 6: Push triballs in from side of goal
	setMove(0, 60, 0, 100, 600);
	states.setShooterState(stateMachine::shooter_state::FIRE);
	// states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMove(28, 50, 120, 120, 900);
	pros::delay(200);
	turn_target = 0;
	waitUntilSettled(0);
	setMove(-8, 0, 120, 120, 600);
	waitUntilSettled(0);
	setMove(20, 10, 120, 120, 600);
	waitUntilSettled(0);
	setMove(-10, 0, 120, 120, 600);
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

void progSkills() {
	// globalPose.setPoint(22.5, 17.5, 0);
	globalPose.setPoint(24, 24 - BASE_Y_OFFSET, 0); // as far left as possible on matchload bar, right drive motor in line with edge of tile

	// 1: line up to matchload 
	// setMove(26, 315, 120, 120, 1000, false);
	// waitUntilNear(13, 0);
	// turn_target = 0;
	// waitUntilSettled(0);
	// setMoveToPoint(15, 30, 1000, true);
	// waitUntilSettled(0);

	// states.setWingState(stateMachine::wing_state::LEFT_OUT);
	// pros::delay(200);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// setMoveToPoint(12, 27, 100, 120, 1200, false);
	// waitUntilSettled(200);
	// setMove(0, 260, 0, 100, 700);
	// waitUntilSettled(0);
	// setMove(6, 260, 650);
	// waitUntilSettled(0);

	setMove(0, 320, 0, 100, 700);
	waitUntilSettled(0);
	setMove(12, 320, 800);
	waitUntilSettled(0);
	// setMove(0, 260, )
	setMoveToPoint(120, 62, 0, 100, 800, true); // (120, 70)
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);

	matchloadState = true;
	pros::delay(28000); // 26 seconds
	matchloadState = false;
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	pros::delay(100);

	//  2: Cross field  //
	// get off of matchload bar and push preload in goal
	setMoveToPoint(36, 13, 60, 120, 1200, true);
	pros::delay(500);
	max_translate_power = 100;
	waitUntilSettled(0);
	setMoveToPoint(108, 12, 100, 120, 2000, true);
	waitUntilSettled(0);

	// 4: Score first few triballs in from side of goal  //
	setMoveToPoint(130, 25, 100, 120, 900, true);
	waitUntilSettled(0);
	setMoveToPoint(132, 44, 100, 120, 900, true);
	pros::delay(500);
	max_translate_power = 120;
	waitUntilSettled(0);
	// back up and push again
	setMove(10, 180, 120, 120, 600);
	waitUntilSettled(0);
	setMove(-20, 180, 120, 120, 700);
	waitUntilSettled(0);
	setMoveToPoint(132, 32, 700, false);
	waitUntilSettled(0);

	// 5: Diagonal push from right of goal
	setMoveToPoint(86, 36, 10, 120, 1400, false);
	pros::delay(500);
	max_translate_power = 100;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	// face goal
	setMoveToPoint(84, 50, 80, 120, 800, false);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OFF);
	setMove(0, 45, 0, 100, 800);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(200);
	setMoveToPoint(122, 76, 120, 100, 1800, false); // (120, 74)
	pros::delay(500);
	states.setShooterState(stateMachine::shooter_state::FIRE);
	waitUntilSettled(0);
	// second push
	setMove(-6, 90, 500);
	waitUntilSettled(0);
	setMove(15, 90, 120, 120, 500);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	// 6: Back to mid and push diagonally from the left side
	setMoveToPoint(84, 60, 120, 120, 1500, true);
	waitUntilSettled(0);
	setMoveToPoint(84, 106, 10, 100, 1400, false);
	pros::delay(500);
	max_translate_power = 100;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	setMove(0, 150, 0, 100, 800);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OFF);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(200);
	setMoveToPoint(119, 68, 120, 100, 1800, false);
	waitUntilSettled(0);
	// second push
	setMove(-6, 90, 500);
	waitUntilSettled(0);
	setMove(15, 90, 120, 120, 500);
	waitUntilSettled(0);
	
	// 7: Back to mid
		// setMoveToPoint(94, 70, )
	// setMove(-10, 90, 120, 120, 800);
	// waitUntilSettled(0);

	// 7: If we have time, push from left side of goal
	setMoveToPoint(92, 72, 120, 120, 1000, true);
	waitUntilSettled(0);
	setMoveToPoint(118, 123, 10, 100, 1800, false);
	pros::delay(400);
	max_translate_power = 120;
	waitUntilSettled(0);

	setMoveToPoint(140, 96, 0, 100, 800, true);
	waitUntilSettled(0);
	setMove(-35, 315, 120, 120, 1200);
	pros::delay(350);
	turn_target = 0;
	waitUntilSettled(0);
	setMove(7, 0, 120, 120, 800);
	waitUntilSettled(0);
}
