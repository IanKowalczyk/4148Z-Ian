#include "main.h"

/**
 * USE C++ VERSION BEFORE 1.19.4 (otherwise bad things happen)
*/


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::Task inertialInit([] {inertial.reset(true);});
	pros::Task stateMachineTask(stateHandler);
	pros::Task GUI(initGUI);
	// setShooterBrakeMode(pros::E_MOTOR_BRAKE_COAST);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	climbDown(); // be careful with this one
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
pros::Task autoMovement(autoMovementTask);
void autonomous() {
	// **** Init **** //
	displayInfo = false;
	// odom init //
	resetOdomSensors();
	globalPose.setPoint(0.0, 0.0, 0);

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

	// **** NEW AUTOS **** //
	// defenseWP();	// 1
	// defenseElims();	// 2
	// sixBallWP();	// 4
	// sixBallElims();	// 5
	// newProgSkillsMRL();	// 6

	// **** Autoselector **** //
	if(autoToRun == 1) {
		defenseWP();
	}
	if(autoToRun == 2) {
		defenseElims();
	}
	if(autoToRun == 3) {
		newSixBall(sixBall_mode::BAR); 
		 // defenseAuto(defense_auto_mode::THREE_BALL); // defenseAuto(defense_auto_mode::FOUR_BALL);
	}
	if(autoToRun == 4) {
		sixBallWP();
	}
	if(autoToRun == 5) {
		sixBallElims(); //
	}
	if(autoToRun == 6) {
		newProgSkillsMRL();
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// **** init **** //
	autoMovement.suspend();
	controller.rumble("-");
	// displayInfo = true;

	// **** default states **** //
	states.setWingState(stateMachine::wing_state::WINGS_STOWED);
	states.setIntakeState(stateMachine::intake_state::OFF);

	// **** local variables **** //
	int opcontrolStartTime = pros::c::millis();

	while(true) {
		// **** Auto Macro **** //
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			autoMovement.resume();
			pros::Task progInDriver(progFirstHalf);
			// exit once driver moves joystick
			while(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) < 50) {pros::delay(20);}
			progInDriver.suspend();
			autoMovement.suspend();
			// set default states
			states.setWingState(stateMachine::wing_state::WINGS_STOWED);
			states.setIntakeState(stateMachine::intake_state::OFF);
			matchloadState = false;
		}

		// **** Subsystems **** //
		/* Drive */
		splitArcade(pros::E_MOTOR_BRAKE_COAST);
		/* Intake */
		intakeOpControl(pros::E_CONTROLLER_DIGITAL_R2, 
						pros::E_CONTROLLER_DIGITAL_R1);
		/* Shooter */
		shooterOpControl(pros::E_CONTROLLER_DIGITAL_B);
		/* Wing */
		wingOpControl(pros::E_CONTROLLER_DIGITAL_L1);
		/* Matchload */
		matchloadOpControl(pros::E_CONTROLLER_DIGITAL_L2);
		/* Climb */
		climbOpControl(pros::E_CONTROLLER_DIGITAL_Y, 
					pros::E_CONTROLLER_DIGITAL_RIGHT,
					pros::E_CONTROLLER_DIGITAL_DOWN);
		/* Brake */
		// brakeOpControl(pros::E_CONTROLLER_DIGITAL_X);

		// **** Util **** //
		matchTimerRumble(opcontrolStartTime);	// Rumble for match time

		// loop delay
		pros::delay(20);	
	}
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
// void on_center_button() {
// 	static bool pressed = false;
// 	pressed = !pressed;
// 	if(pressed) {
// 		pros::lcd::set_text(2, "I was pressed!");
// 	}
// 	else {
// 		pros::lcd::clear_line(2);
// 	}
// }