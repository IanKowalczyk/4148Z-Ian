#include "main.h"
#include "lib_header/api/lib_api.h"

/**
 * USE C++ VERSION BEFORE 1.19.4 (otherwise bad things happen) (aka PROS doesn't build)
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
	oneIntakeMode = false;
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

	// **** NEW AUTOS **** //
	// defenseWP();	// 1
	// defenseElims();	// 2
	// sixBallWP();	// 4
	// sixBallElims();	// 5
	// newProgSkillsMRL();	// 6

	// **** Autoselector **** //
	if(autoToRun == 1) {
		defenseWP();
		// sixBallWP();
	}
	if(autoToRun == 2) {
		defenseElims();
	}
	if(autoToRun == 3) {
		defenseAuto(defense_auto_mode::THREE_BALL); // defenseAuto(defense_auto_mode::FOUR_BALL);
	}
	if(autoToRun == 4) {
		sixBallWP();
	}
	if(autoToRun == 5) {
		sixBallElims(); //
	}
	if(autoToRun == 6) {
		// newProgSkillsMRL();
		newSixBall(sixBall_mode::BAR); 
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
			stopShooter(pros::E_MOTOR_BRAKE_COAST);
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
