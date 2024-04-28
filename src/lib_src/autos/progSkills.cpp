#include "lib_header/autos_h/progSkills.h"

// ******** Prog Skills ********//
void newProgSkillsMRL() { // PUSHED MID, RIGHT, LEFT
	// init
	globalPose.setPoint(22, 17, 0); // as far left as possible on matchload bar, right drive motor in line with edge of tile
	int MATCHLOAD_TIME = 23000; // 23000 ms - 23 seconds
	if(MATCHLOAD_TIME > 23000) {MATCHLOAD_TIME = 23000;}
	int ANGLE_TO_GOAL = 66.4; // angle = 74
	// states.setShooterState(stateMachine::shooter_state::FIRE);

	/** 1: Push two preloads in and line up to matchload bar */ 
		pros::delay(100);
	setMove(34, 320, 100, 100, 900); // 800 ms, DONT FORGET TO CHANGE
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		pros::delay(400);
		turn_target = 0;
	waitUntilSettled(0);
		// states.setShooterState(stateMachine::shooter_state::FIRE);
	setMoveToPoint(25, 17, 80, 110, 1000, true); // (26, 17) // BACK TO BAR
		states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	// setMoveToPoint(120, 50, 0, 100, 800, false); // turn to face goal
	setMove(0, ANGLE_TO_GOAL, 0, 120, 700);
	waitUntilSettled(0);

	// Back up to bar
	setMove(-6.7, ANGLE_TO_GOAL, 60, 80, MATCHLOAD_TIME - 2000);
		pros::delay(230);
		max_drive_power = 10;

	// Matchload
		pros::delay(400);
		setShooter(-70);
		// matchloadState = true;
		pros::delay(MATCHLOAD_TIME); // 28 seconds
		stopShooter(pros::E_MOTOR_BRAKE_COAST);
		// matchloadState = false;
		pros::delay(100);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	/** 2: Cross field */
	// get off of matchload bar
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMoveToPoint(36, 12, 60, 120, 700, false);
		pros::delay(300);
		max_translate_power = 120;
	waitUntilSettled(0);
	setMoveToPoint(108, 11, 120, 120, 1800, false); // 100 max translate
	waitUntilSettled(0);
	
	/** 3: Score first few triballs in from side of goal */
		states.setWingState(stateMachine::wing_state::LEFT_OUT);
	setMoveToPoint(130, 25, 100, 120, 600, false);
	waitUntilSettled(0);
	setMoveToPoint(132, 44, 90, 120, 800, false);
	// states.setWingState(stateMachine::wing_state::LEFT_OUT);
		pros::delay(400);
		max_translate_power = 120;
	waitUntilSettled(0);
		// BACK UP AND PUSH AGAIN
		setMove(-13, 0, 120, 120, 600);
		waitUntilSettled(200);
		setMove(20, 0, 100, 120, 800);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	// setMove(-12, 0, 120, 120, 400);
	// waitUntilSettled(0);
	setMoveToPoint(132, 32, 700, true);
	waitUntilSettled(0);

	/** 4: Push from mid */
	setMove(0, 270, 0, 120, 500);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	// states.setWingState(stateMachine::wing_state::LEFT_OUT);
	setMoveToPoint(85, 34, 90, 120, 1000, false);	// (85, 35)
	// pros::delay(200);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);

	setMoveToPoint(83, 73, 10, 100, 1000, false);
		pros::delay(300);
		max_translate_power = 100;
	waitUntilSettled(0);
	setMove(0, 90, 0, 100, 500);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		pros::delay(200);
	setMoveToPoint(126, 66, 50, 100, 1400, false); // (126, 68)
		pros::delay(400);
		max_translate_power = 120;
	// for(int i=0; i<(500/10); i++) {
	// 	pros::delay(10);
	// 	max_translate_power += 120/25;
	// }
	waitUntilSettled(0);
		// SECOND PUSH
		// setMove(-16, 90, 120, 120, 600);
		// waitUntilSettled(0);
		// setMove(30, 95, 120, 120, 800);
		// waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
		pros::delay(150);

	// DIAG PUSH FROM RIGHT SIDE
	// FACE GOAL
	setMoveToPoint(90, 72, 800, true);
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	setMoveToPoint(77, 30, 0, 100, 1300, true); // (77, 32)
		pros::delay(260);
		max_translate_power = 110;
	waitUntilSettled(0);
		/** sus right push */
			// setMoveToPoint(93, 34, 800, false);
			// states.setWingState(stateMachine::wing_state::WINGS_OUT);
			// waitUntilSettled(0);
			// setMoveToPoint(98, 55, 70, 90, 600, false);
			// states.setIntakeState(stateMachine::intake_state::OUTTAKING);
			// waitUntilSettled(0);
			// setMoveToPoint(126, 65, 800, false);
			// waitUntilSettled(0);

	/** CURVED PUSH FROM RIGHT SIDE*/
		// setMove(14, 94, 1, 100, 1000);
		// pros::delay(400);
		// max_drive_power = 100;
		// waitUntilSettled(0);
		// setMove(0, 20, 0, 100, 500);
		// 	states.setWingState(stateMachine::wing_state::WINGS_OUT);
		// 	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		// 	pros::delay(100);
		// waitUntilSettled(0);
		// setMoveToPoint(98, 55, 70, 90, 600, false);
		// waitUntilSettled(0);

	/** JUST TURN AND PUSH FROM RIGHT SIDE*/
		setMove(0, 60, 0, 120, 500);
			pros::delay(300);
			states.setWingState(stateMachine::wing_state::WINGS_OUT);
			states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		waitUntilSettled(0);

	setMoveToPoint(126, 65, 800, false);
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(0, 90, 0, 100, 500);
		waitUntilSettled(0);
		setMove(-15, 90, 120, 120, 600);
		// states.setWingState(stateMachine::wing_state::LEFT_OUT);
		waitUntilSettled(200);
		setMove(25, 90, 125, 120, 800, true);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	pros::delay(150);


	/** 5: Push diagonally from the left side */ 
	setMoveToPoint(85, 54, 800, true);
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::INTAKING);
	setMoveToPoint(85, 108, 0, 100, 1250, false); // (85, 108)
		pros::delay(300);
		max_translate_power = 80;
	waitUntilSettled(0);
	setMove(16, 90, 1, 120, 900);
		pros::delay(400);
		max_drive_power = 100;
	waitUntilSettled(0);
	setMove(0, 160, 0, 100, 500);
	waitUntilSettled(0);
		states.setWingState(stateMachine::wing_state::WINGS_OUT);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		pros::delay(200);
	// setMoveToPoint(96, 83, 70, 90, 800, false); // (98, 86)
	// waitUntilSettled(0);
	setMoveToPoint(126, 62, 900, false); // (125, 83)
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(0, 90, 0, 120, 500);
		waitUntilSettled(0);
		setMove(-15, 90, 120, 120, 600);
		// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		waitUntilSettled(200);
		setMove(22, 90, 125, 120, 800, true);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	pros::delay(150);


	/** 7: Push from left side of goal */
	setMoveToPoint(95, 74, 110, 120, 700, true); // (92, 70)
		states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	setMoveToPoint(114, 140, 125, 125, 1300, false); // hit hang bar at (108, 130) // (114, 130)
		states.setIntakeState(stateMachine::intake_state::INTAKING);
		pros::delay(650);
		states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(0);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMove(0, 115, 0, 100, 500);
	waitUntilSettled(0);
	// setMoveToPoint(125, 112, 110, 120, 900, false); // (132, 116)
	setMove(17, 115, 120, 120, 600);
		pros::delay(300);
		turn_target = 120;
	waitUntilSettled(0);

		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMoveToPoint(130, 88, 120, 120, 900, false);
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(-12, 160, 120, 120, 500);
		waitUntilSettled(200);
		setMove(22, 160, 125, 120, 700, true);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// states.setIntakeState(stateMachine::intake_state::OFF);
	setMoveToPoint(108, 128, 120, 120, 900, true);
	waitUntilSettled(0);

	// // OPTIONAL : CLIMB
	// leftClimb.set_value(true);
	// rightClimb.set_value(true);
	climbUp();
	setMove(0, 280, 0, 120, 600);
	waitUntilSettled(0);
	// setMoveToPoint(65, 126, 120, 120, 1100, false); // sometimes drifts to the right
	setMove(41, 270, 120, 100, 1000);
	waitUntilSettled(0);
	climbDown();
		states.setShooterState(stateMachine::shooter_state::FIRE);
		pros::delay(400);
	while(inertial.get_roll() > 8) {
		// matchloadState = true;
		setShooter(-127);
		pros::delay(5);
	}
	setShooter(0);
	// matchloadState = false;
}

// ******** NOT IN USE ******** //
void newProgSkillsRLM() { // PUSHES RIGHT, LEFT, MIDDLE
	// init
	globalPose.setPoint(22, 17, 0); // as far left as possible on matchload bar, right drive motor in line with edge of tile
	int MATCHLOAD_TIME = 24000; // 26000 ms - 26 seconds
	if(MATCHLOAD_TIME > 24000) {MATCHLOAD_TIME = 24000;}
	int ANGLE_TO_GOAL = 65; // angle = 74
	states.setShooterState(stateMachine::shooter_state::FIRE);

	/** 1: Push two preloads in and line up to matchload bar */ 
	pros::delay(100);
	setMove(34, 320, 100, 100, 900); // 800 ms, DONT FORGET TO CHANGE
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	pros::delay(400);
	turn_target = 0;
	waitUntilSettled(0);
	setMoveToPoint(25, 17, 80, 110, 1000, true); // (26, 17) // BACK TO BAR
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	// setMoveToPoint(120, 50, 0, 100, 800, false); // turn to face goal
	setMove(0, ANGLE_TO_GOAL, 0, 100, 800);
	waitUntilSettled(0);

	// Back up to bar
	setMove(-6.5, ANGLE_TO_GOAL, 60, 80, MATCHLOAD_TIME - 2000);
	pros::delay(200);
	max_drive_power = 10;

	// Matchload
	pros::delay(200);
	matchloadState = true;
	pros::delay(MATCHLOAD_TIME); // 28 seconds
	matchloadState = false;
	pros::delay(100);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	/** 2: Cross field */
	// get off of matchload bar
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMoveToPoint(36, 12, 60, 120, 750, false);
	pros::delay(300);
	max_translate_power = 120;
	waitUntilSettled(0);
	setMoveToPoint(108, 11, 100, 120, 1900, false);
	waitUntilSettled(0);
	
	/** 3: Score first few triballs in from side of goal */
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	setMoveToPoint(130, 25, 100, 120, 600, false);
	waitUntilSettled(0);
	setMoveToPoint(132, 44, 90, 120, 800, false);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(400);
	max_translate_power = 120;
	waitUntilSettled(0);
		// BACK UP AND PUSH AGAIN
		setMove(-13, 0, 120, 120, 600);
		waitUntilSettled(300);
		setMove(20, 0, 100, 120, 800);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	// setMove(-12, 0, 120, 120, 400);
	// waitUntilSettled(0);
	setMoveToPoint(132, 32, 700, true);
	waitUntilSettled(0);

	/** 4: Diagonal push from right of goal */
	setMove(0, 270, 0, 100, 700);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	setMove(8, 300, 100, 80, 600);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMoveToPoint(83, 35, 0, 120, 1100, false);	// x= 86, y = 36
	states.setIntakeState(stateMachine::intake_state::OFF);
	pros::delay(200);
	max_translate_power = 100;
	pros::delay(400);
	target_y = 32;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	// FACE GOAL
	setMoveToPoint(125, 59, 0, 100, 1500, false); // (125, 61)
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(400);
	max_translate_power = 120;
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(0, 90, 0, 100, 600);
		waitUntilSettled(0);
		setMove(-15, 90, 120, 120, 600);
		// states.setWingState(stateMachine::wing_state::LEFT_OUT);
		waitUntilSettled(200);
		setMove(20, 90, 120, 120, 800);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	pros::delay(200);

	/** 5: Push diagonally from the left side */ 
	setMoveToPoint(85, 30, 10, 120, 1100, true); // (84, 34)
	pros::delay(300);
	max_translate_power = 90;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	setMoveToPoint(83, 122, 0, 100, 1700, false);
	pros::delay(300);
	max_translate_power = 100;
	pros::delay(600);
	max_translate_power = 70;
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	setMove(0, 150, 0, 70, 900);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	setMoveToPoint(123, 66, 100, 105, 1400, false); // (123, 70)
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	// pros::delay(350);
	// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(0, 90, 0, 100, 600);
		waitUntilSettled(0);
		setMove(-15, 90, 120, 120, 600);
		// states.setWingState(stateMachine::wing_state::RIGHT_OUT);
		waitUntilSettled(200);
		setMove(20, 90, 120, 120, 800);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	pros::delay(200);

	/** 6: Final pushes from mid */ 
	setMoveToPoint(86, 110, 1100, true);
	waitUntilSettled(0);
	setMoveToPoint(85, 73, 0, 100, 1100, false);
	pros::delay(400);
	max_translate_power = 100;
	waitUntilSettled(0);
	setMove(0, 90, 0, 100, 500);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	waitUntilSettled(0);
	setMoveToPoint(126, 68, 100, 100, 1500, false); // (126, 72)
	pros::delay(400);
	max_translate_power = 120;
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(-16, 90, 120, 120, 600);
		waitUntilSettled(0);
		setMove(20, 95, 120, 120, 800);
		waitUntilSettled(0);

	/** 7: Push from left side of goal */
	setMoveToPoint(92, 70, 100, 120, 800, true);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	setMoveToPoint(114, 130, 1400, false); // hit hang bar at (108, 130)
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(800);
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(0);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	setMoveToPoint(132, 116, 0, 100, 900, false);
	pros::delay(500);
	max_translate_power = 100;
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMoveToPoint(133, 88, 900, false);
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(-10, 180, 120, 120, 600);
		waitUntilSettled(300);
		setMove(20, 180, 120, 120, 800);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// states.setIntakeState(stateMachine::intake_state::OFF);
	setMoveToPoint(108, 128, 120, 120, 1200, true);
	waitUntilSettled(0);

	// // OPTIONAL : CLIMB
	// leftClimb.set_value(true);
	// rightClimb.set_value(true);
	climbUp();
	setMove(0, 280, 1000);
	waitUntilSettled(0);
	// setMoveToPoint(64.5, 130, 120, 120, 1300, false); // sometimes drifts to the right
	setMove(38, 270, 120, 100, 770);
	waitUntilSettled(0);
	climbDown();
	states.setShooterState(stateMachine::shooter_state::FIRE);
	pros::delay(400);
	while(inertial.get_roll() > 8) {
		matchloadState = true;
		// setShooter(-100);
		pros::delay(5);
	}
	// setShooter(0);
	matchloadState = false;
}

// ******** NOT IN USE ******** //
void progSkills() { // OLD - 2 PUSHES FROM RIGHT AND LEFT
	// init
	globalPose.setPoint(22, 17, 0); // as far left as possible on matchload bar, right drive motor in line with edge of tile
	int matchloadTimer = 24000; // 26000 ms - 26 seconds
	int angleToGoal = 74; // angle = 70
	states.setShooterState(stateMachine::shooter_state::FIRE);

	/** 1: Push two preloads in and line up to matchload bar */ 
	pros::delay(100);
	setMove(34, 320, 100, 100, 900); // 800 ms, DONT FORGET TO CHANGE
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	pros::delay(400);
	turn_target = 0;
	waitUntilSettled(0);
	setMoveToPoint(20, 20, 100, 100, 700, true); // (20, 25) // BACK TO BAR
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	// setMoveToPoint(120, 50, 0, 100, 800, false); // turn to face goal
	setMove(0, angleToGoal, 0, 100, 800);
	waitUntilSettled(0);

	// Back up to bar
	setMove(-8, angleToGoal, 60, 80, matchloadTimer - 2000);
	pros::delay(200);
	max_drive_power = 10;

	// Matchload
	pros::delay(200);
	matchloadState = true;
	pros::delay(matchloadTimer); // 28 seconds
	matchloadState = false;
	pros::delay(100);
	// states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	/** 2: Cross field */
	// get off of matchload bar
	setMoveToPoint(36, 12, 60, 120, 760, false);
	pros::delay(400);
	max_translate_power = 100;
	waitUntilSettled(0);
	setMoveToPoint(108, 12, 100, 120, 2000, false);
	waitUntilSettled(0);

	/** 3: Score first few triballs in from side of goal */
	setMoveToPoint(130, 25, 100, 120, 600, false);
	waitUntilSettled(0);
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMoveToPoint(132, 44, 90, 120, 800, false);
	states.setWingState(stateMachine::wing_state::LEFT_OUT);
	pros::delay(400);
	max_translate_power = 120;
	waitUntilSettled(0);
		// BACK UP AND PUSH AGAIN
		setMove(-14.5, 0, 120, 120, 600);
		waitUntilSettled(300);
		setMove(20, 0, 120, 120, 600);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	// setMove(-12, 0, 120, 120, 400);
	// waitUntilSettled(0);
	setMoveToPoint(132, 32, 700, true);
	waitUntilSettled(0);

	/** 4: Diagonal push from right of goal */
	setMoveToPoint(83, 34, 10, 120, 1300, false);	// x= 86, y = 36
	states.setIntakeState(stateMachine::intake_state::OFF);
	pros::delay(500);
	max_translate_power = 100;
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	// FACE GOAL
	// setMoveToPoint(84, 50, 80, 120, 800, false);
	// waitUntilSettled(0);
	// states.setIntakeState(stateMachine::intake_state::OFF);
	setMove(0, 30, 0, 100, 700);
	waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);

	pros::delay(400);
	setMoveToPoint(103, 60, 90, 100, 800, false); // half push: (103, 64)
	waitUntilSettled(0);
	setMoveToPoint(130, 64, 100, 120, 900, false); // final push
	pros::delay(200);
	max_translate_power = 120;
	waitUntilSettled(0);

	// setMoveToPoint(122, 73, 100, 105, 1800, false); // (120, 76)
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(-17, 90, 120, 120, 600);
		states.setWingState(stateMachine::wing_state::LEFT_OUT);
		waitUntilSettled(200);
		setMove(20, 90, 120, 120, 700);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);

	/** 5: Back to mid and push diagonally from the left side */ 
	setMoveToPoint(83, 70, 120, 120, 900, true);
	states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	setMoveToPoint(83, 100, 10, 100, 1100, false); // (84, 100)
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	pros::delay(440);
	max_translate_power = 100;
	waitUntilSettled(0);
	// setMoveToPoint(92, 108, 600, false);
	setMove(0, 160, 0, 100, 800); // turn 170
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	states.setWingState(stateMachine::wing_state::WINGS_OUT);
	pros::delay(400);
	setMoveToPoint(92, 82, 500, false); // half push: 
	waitUntilSettled(0);
	setMoveToPoint(130, 68, 100, 120, 900, false); // final push
	pros::delay(300);
	max_translate_power = 120;
	// setMoveToPoint(119, 68, 100, 105, 1800, false);
	waitUntilSettled(0);
		// SECOND PUSH
		setMove(-17, 90, 120, 120, 600);
		waitUntilSettled(200);
		setMove(20, 90, 120, 120, 700);
		waitUntilSettled(0);

	/** 6: If we have time, push from left side of goal */ 
	setMoveToPoint(92, 70, 100, 120, 800, true);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	waitUntilSettled(0);
	setMoveToPoint(110, 130, 1400, false); // hit hang bar at (108, 130)
	states.setIntakeState(stateMachine::intake_state::INTAKING);
	waitUntilSettled(0);
	setMoveToPoint(132, 116, 0, 100, 900, false);
	pros::delay(500);
	max_translate_power = 100;
	states.setWingState(stateMachine::wing_state::RIGHT_OUT);
	waitUntilSettled(0);
	states.setIntakeState(stateMachine::intake_state::OUTTAKING);
	setMoveToPoint(133, 88, 900, false);
	waitUntilSettled(0);

		// SECOND PUSH
		setMove(-13, 180, 120, 120, 600);
		waitUntilSettled(0);
		setMove(20, 180, 120, 120, 700);
		waitUntilSettled(0);
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	// states.setIntakeState(stateMachine::intake_state::OFF);
	setMoveToPoint(108, 128, 120, 120, 1200, true);
	waitUntilSettled(0);

	// // OPTIONAL : CLIMB
	// leftClimb.set_value(true);
	// rightClimb.set_value(true);
	climbUp();
	setMove(0, 280, 1000);
	waitUntilSettled(0);
	setMoveToPoint(65, 130, 120, 120, 1300, false);
	// pros::delay(600);
	// max_translate_power = 120;
	states.setShooterState(stateMachine::shooter_state::FIRE);
	waitUntilSettled(200);
	climbDown();
	pros::delay(600);
	while(inertial.get_roll() > 8) {
		matchloadState = true;
		// setShooter(-100);
		pros::delay(5);
	}
	// setShooter(0);
	matchloadState = false;
}

// driver macro to run first half of prog, shoots forever
void progFirstHalf() { // yea
	// init
	globalPose.setPoint(22, 17, 0); // as far left as possible on matchload bar, right drive motor in line with edge of tile
	int MATCHLOAD_TIME = 23000; // 23000 ms - 23 seconds
	if(MATCHLOAD_TIME > 23000) {MATCHLOAD_TIME = 23000;}
	int ANGLE_TO_GOAL = 66.4; // angle = 74

	/** 1: Push two preloads in and line up to matchload bar */ 
		pros::delay(100);
	setMove(34, 320, 100, 100, 900); // 800 ms, DONT FORGET TO CHANGE
		states.setIntakeState(stateMachine::intake_state::OUTTAKING);
		pros::delay(400);
		turn_target = 0;
	waitUntilSettled(0);
	setMoveToPoint(25, 17, 80, 110, 1000, true); // (26, 17) // BACK TO BAR
		states.setIntakeState(stateMachine::intake_state::OFF);
	waitUntilSettled(0);
	// setMoveToPoint(120, 50, 0, 100, 800, false); // turn to face goal
	setMove(0, ANGLE_TO_GOAL, 0, 120, 700);
	waitUntilSettled(0);

	// Back up to bar
	setMove(-6.7, ANGLE_TO_GOAL, 60, 80, MATCHLOAD_TIME - 2000);
		pros::delay(230);
		max_drive_power = 10;

	// Matchload
		pros::delay(400);
		setShooter(-70);
		pros::delay(50000);
}
