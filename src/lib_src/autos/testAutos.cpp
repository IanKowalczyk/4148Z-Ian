#include "lib_header/autos_h/testAutos.h"

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

void slowOdomBoxTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(0, 24, 40, 30, 2200, false);
    waitUntilSettled(0);
    setMoveToPoint(24, 24, 40, 30, 2200, false);
    waitUntilSettled(0);
    setMoveToPoint(24, 0, 40, 30, 2200, false);
    waitUntilSettled(0);
    setMoveToPoint(0, 0, 40, 30, 2200, false);
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

void chainedMoveToPointTest() {
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

// From main

	// ******** TESTS ******** //
	// **** Extend moveToPoint test **** //
	// setMoveToPoint(0, 24, 800, false);
	// waitUntilNear(4, 0);
	// extendMoveToPoint(12, 24, 100, 100, 1000, false);
	// waitUntilNear(4, 0);
	// extendMoveToPoint(0, 0, 100, 100, 1000, false);
	// waitUntilSettled(500);
	// setMove(0, 90, 1000);
	// waitUntilSettled(0);

	// globalPose.setPoint(103.5, 17, 1); // newSixBall() // top left of tile
	// states.setWingState(stateMachine::wing_state::RIGHT_OUT);

	/** Forward and backward test */
	// setMoveToPoint(0, 24, 40, 30, 5000, false);
	// waitUntilSettled(0);
	// setMoveToPoint(0, 0, 40, 30, 5000, true);
	// waitUntilSettled(0);
	
	// squigglesTest(); 		// FAILED, turns but doesn't move after chained movement
	// chainedMoveToPoint(); 	// FAILED, turns but doesn't move after first chained to move
	
	// ** waitUntilNear test (WORKS) ** //
	// setMoveToPoint(40, 24, 900, false);
	// waitUntilNear(5, 0);
	// setMoveToPoint(49, 5, 800, true);
	// waitUntilNear(5, 0);
	// setMoveToPoint(0, 0, 1200, true);
	// waitUntilSettled(50000);

	// globalPose.setPoint(120, 14, 321); // angled to face triball near bar; right front wheel in line with intersection of tiles; (24, 14)
	// sixBall(sixBall_mode::BAR);
	// ******** ******** //