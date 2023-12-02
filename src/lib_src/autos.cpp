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
void odomBoxTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(0, 24, 1500, false);
    waitUntilSettled(20);
    setMoveToPoint(24, 24, 1500, false);
    waitUntilSettled(20);
    setMoveToPoint(24, 0, 1500, false);
    waitUntilSettled(20);
    setMoveToPoint(0, 0, 1500, false);
    waitUntilSettled(500);
}
void odomTriangleTest() {
    globalPose.setPoint(0.0, 0.0, 0);
    setMoveToPoint(20, 20, 2000, false);
	waitUntilSettled(20);
	setMoveToPoint(40, 0, 2000, false);
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 2000, false);
	waitUntilSettled(500);
}

void squigglesTest() {
    globalPose.setPoint(0.0, 0.0, 0);   // Initialize position
    setMove(1600, 45, 100, 80, 3000); // right curve
	pros::delay(750);
	setMove(1600, 315, 100, 80, 3000);// left curve
	pros::delay(750);
	setMove(1600, 45, 100, 80, 3000); // small right curve
	pros::delay(500);
	setMove(800, 0, 100, 80, 3000);   // straight
	waitUntilSettled(20);
	setMoveToPoint(0, 0, 1500, false);     // back to origin
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

}

void fourBall() {

}

void progSkills() {
	
}
