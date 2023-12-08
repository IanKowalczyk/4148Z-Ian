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

	// Cata
	states.setCataState(stateMachine::cata_state::FIRE);
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
    setMove(1600, 45, 100, 80, 3000);	// right curve
	pros::delay(750);
	setMove(1600, 315, 100, 80, 3000);	// left curve
	pros::delay(750);
	setMove(1600, 45, 100, 80, 3000);	// small right curve
	pros::delay(500);
	setMove(800, 0, 100, 80, 3000);		// straight
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 1500, false);	// back to origin
	waitUntilSettled(50);
}

void chainedMoveToPoint() {
	// Test: chaining together moveToPoints to run a path
    setMoveToPoint(20, 20, 1500, false);
	// waitUntilSettled(20);
	pros::delay(700);
	setMoveToPoint(40, 0, 1500, false);
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 1500, false);
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

}

void offenseAuto(offense_auto_mode s) {

}

void sixBall() {
	globalPose.setPoint(0, 0, 0);
	
	// **** Rush mid **** //
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	pros::delay(100);
	setMoveToPoint(75, 72, 120, 120, 1800, false);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);

	// 1,2: Score first two mid triballs 
	setMove(0, 90, 0, 100, 800, false);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	setMoveToPoint(120, 72, 120, 120, 1500, false);
	waitUntilSettled(0);
	
	// 3: Grab third triball 
	setMoveToPoint(rightTriball5.x, rightTriball5.y, 120, 120, 2000, true);
	waitUntilNear(28, 0);
	movement_reversed = false;
	max_translate_power = 0;
	pros::delay(600);
	max_translate_power = 120;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);

	// 3: Outtake third triball near matchload station
	setMove(0, 110, 0, 100, 800);
	waitUntilSettled(0);
	setMoveToPoint(108, 34, 120, 120, 1000, false);
	pros::delay(700);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilNear(2, 0);

	// 4: Swing and grab fourth triball
	setMoveToPoint(110, 12, 100, 120, 800, false);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilNear(3, 0);
	setMoveToPoint(72 + BASE_Y_OFFSET, 12, 120, 120, 1200, false);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);

	// 4: Go back to matchload bar
	setMoveToPoint(108, 12, 120, 120, 1200, true);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilNear(1, 0);
	setMove(0, 50, 0, 100, 800);
	waitUntilSettled(0);
	
	// 5: Descore matchload triball (fifth ball)
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	// setMove()
	
}

void fourBall() {

}

void progSkills() {
	globalPose.setPoint(22.5, 17.5, 0); // as far left as possible on matchload bar, right drive motor in line with edge of tile

	// 1: line up to matchload 
	// setMove(26, 315, 120, 120, 1000, false);
	// waitUntilNear(13, 0);
	// turn_target = 0;
	// waitUntilSettled(0);
	// setMoveToPoint(15, 30, 1000, true);
	// waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(200);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMoveToPoint(12, 27, 100, 120, 1200, false);
	waitUntilSettled(0);
	setMove(0, 280, 0, 100, 800);
	waitUntilSettled(0);

	// setMove(6, 280, 800);
	// waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);

	matchloadState = true;
	pros::delay(26000); // 26 seconds
	matchloadState = false;
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	//  2: Cross field  //
	// TODO : get off of matchload bar and push preload in goal
	setMoveToPoint(107, 12, 120, 120, 1500, false);
	pros::delay(400);
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(500);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);

	// 3: Descore from matchload  //
	setMoveToPoint(126, 26.5, 100, 120, 1200, false);
	pros::delay(500);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(0);
	setMove(0, 20, 0, 100, 600);
	waitUntilSettled(0);
	setMove(0, 45, 0, 100, 600);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);

	// 4: Score first few triballs in from side of goal  //
	setMoveToPoint(120 + 11.5, 42.5, 100, 120, 1200, false);
	waitUntilSettled(0);
	// TODO : back up and push again
	setMoveToPoint(126, 24 + 5, 800, true);
	waitUntilSettled(0);

	// 5: Diagonal push from right of goal
	

}
