#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "main.h"

// ******** Drive Constants ******** //
extern double TURN_SENS;
extern double DRIVE_BRAKE_THRESHOLD;


// ******** Intake Constants ******** //
extern int INTAKE_CLOSE_THRESHOLD;
extern int INTAKE_OPEN_THRESHOLD;


// ******** Shooter Constants ******** //
extern int SHORT_PULLBACK_TICKS;
extern int FULL_PULLBACK_TICKS;
extern int MIN_FIRE_TIME;
extern int PULLBACK_TIMEOUT;
extern int PULLBACK_THRESHOLD;
extern int FIRE_DELAY;

// ******** Odom Constants ******** //
extern double TRACKING_WHEEL_DIAMETER;
extern double FRONT_ENC_OFFSET;
extern double SIDE_ENC_OFFSET;
extern double BASE_X_OFFSET;
extern double BASE_Y_OFFSET; 
extern double TOTAL_Y_OFFSET;


// ******** PID Constants ******** //
extern double movekP;
extern double movekD;
extern double turnkP;
extern double turnkI;


// **************** Movement Constants **************** //
extern int DRIVE_SLEW_RATE;
extern int TURN_SLEW_RATE;
extern int SETTLE_THRESHOLD;
extern int NEAR_TARGET_THRESHOLD;
extern double DISTANCE_SETTLE_THRESHOLD;
extern double TURN_SETTLE_THRESHOLD;
extern double DRIVE_VELOCITY;
extern double TURN_VELOCITY;


// ******** Setpoints ******** //
// extern Point leftTriball1;		// Left mid - auto line (48, 72)
// extern Point leftTriball2;		// Left pole - auto line (68, 72)
// extern Point rightTriball3;	    // Right pole - auto line (76, 72)
// extern Point rightTriball4;	    // Right mid - auto line (96, 72)
// extern Point rightTriball5;	    // Right pole, in line with goal post (76, 48)
// extern Point hangBarTriball;	// Underneath hang bar (72, 12)

// extern Point leftBottomMatchload;		// In front of left bottom matchload station (20, 20)
// extern Point rightBottomMatchload;	    // In front of right bottom matchload station (124, 20)
// extern Point leftTopMatchload;		    // In front of left top matchload station (20, 124)
// extern Point rightTopMatchload;		    // In front of right top matchload  (124, 124)


// ******** Conversion Rates ******** //
extern double PCT_TO_VOLT;
extern double VOLT_TO_PCT;

extern double RAD_TO_DEG;
extern double DEG_TO_RAD;

/** OLD 2.75 in converstion ratios */
extern double DRIVE_INCH_TO_DEG_275;
extern double DRIVE_DEG_TO_INCH_275;

/** THEORETICAL 2.00 in conversion ratios */
extern double DRIVE_INCH_TO_DEG_2IN;
extern double DRIVE_DEG_TO_INCH_2IN;

/** NEW / OBSERVED 2.00 in conversion ratios */
// extern double DRIVE_INCH_TO_DEG_2IN = 56.25;           // (1350 / 24) ~ 56.25 (don't use in this form)
// extern double DRIVE_DEG_TO_INCH_2IN = 0.0177777777;    // (24 / 1350) ~ 0.01777777 (don't use in this form)


#endif