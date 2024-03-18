#include "lib_header/robot_h/constants.h"

// ******** SUBSYSTEM Constants ******** //
// Drive
double TURN_SENS = 0.8;
double DRIVE_BRAKE_THRESHOLD = 45;  // 45 RPM

// Intake
int INTAKE_CLOSE_THRESHOLD = 300;   // 200 ms
int INTAKE_OPEN_THRESHOLD = 200;    // 200 ms

// Shooter
int SHORT_PULLBACK_TICKS = 4500;    // In centidegrees (100 * degrees)  // 4800
int FULL_PULLBACK_TICKS = 0;        // In centidegrees (100 * degrees) 
int MIN_FIRE_TIME = 200;    // used to be 200ms 
int PULLBACK_TIMEOUT = 400;        // 1000 ms
int PULLBACK_THRESHOLD = 700;       // How close we want to get to the pullback value before stopping the cata (to mitigate overshoot)
int FIRE_DELAY = 120;               // 140 ms


// ******** AUTO Constants ******** //
// Odom
double TRACKING_WHEEL_DIAMETER = 2.00; // 2.00 inches
double FRONT_ENC_OFFSET = 1/4;      // Front enc offset to the left of tracking center (inches) // 1/4
double SIDE_ENC_OFFSET = -3.5;      // Side enc offset to tracking center (inches) // old : 5.5 in
double BASE_X_OFFSET = 13.5/2;      // robot base width: 13.5 in
double BASE_Y_OFFSET = 14/2;        // robot base length: 14 in
double TOTAL_Y_OFFSET = 17.5/2;     // robot length: 14 in + 3.5 in to tip of intake sled

// Auto Movement
int DRIVE_SLEW_RATE = 120/15;           // 150 ms to accelerate = 15 iterations; 120 (basically max power) / 15 (iterations)
int TURN_SLEW_RATE = 120/15;            // 150 ms to accelerate ... TUNE LATER
int SETTLE_THRESHOLD = 5;               // 50 ms: 5 iterations * 10 ms loop // Used to be 50ms
int NEAR_TARGET_THRESHOLD = 2;          // 2 inches
double DISTANCE_SETTLE_THRESHOLD = 1;   // 1 inch
double TURN_SETTLE_THRESHOLD = 1.5;     // 1.5 degrees
double DRIVE_VELOCITY = 39.67; // Inches per second
double TURN_VELOCITY = 180;    // Degrees per second

// // Setpoints
// Point leftTriball1(48, 72);		// Left mid - auto line (48, 72)
// Point leftTriball2(68, 72);		// Left pole - auto line (68, 72)
// Point rightTriball3(76, 72);	// Right pole - auto line (76, 72)
// Point rightTriball4(96, 72);	// Right mid - auto line (96, 72)
// Point rightTriball5(76, 48);	// Right pole, in line with goal post (76, 48)
// Point hangBarTriball(72, 12);	// Underneath hang bar (72, 12)

// Point leftBottomMatchload(20, 20);		// In front of left bottom matchload station (20, 20)
// Point rightBottomMatchload(124, 20);	// In front of right bottom matchload station (124, 20)
// Point leftTopMatchload(20, 124);		// In front of left top matchload station (20, 124)
// Point rightTopMatchload(124, 124);		// In front of right top matchload  (124, 124)


// ******** CONVERSION RATES ******** //
double PCT_TO_VOLT = 127 / 100;
double VOLT_TO_PCT = 100 / 127;

double RAD_TO_DEG = 180 / M_PI;
double DEG_TO_RAD = M_PI / 180;

/** OLD 2.75 in converstion ratios */
double DRIVE_INCH_TO_DEG_275 = 360 / (2.75 * M_PI);
double DRIVE_DEG_TO_INCH_275 = (2.75 * M_PI) / 360;

/** THEORETICAL 2.00 in conversion ratios */
double DRIVE_INCH_TO_DEG_2IN = 360 / (2.00 * M_PI); // 57.29577
double DRIVE_DEG_TO_INCH_2IN = (2.00 * M_PI) / 360; // 0.017453 

/** NEW / OBSERVED 2.00 in conversion ratios */
// double DRIVE_INCH_TO_DEG_2IN = 56.25;           // (1350 / 24) ~ 56.25 (don't use in this form)
// double DRIVE_DEG_TO_INCH_2IN = 0.0177777777;    // (24 / 1350) ~ 0.01777777 (don't use in this form)


// ******** TIMER Constants ******** //

int OPCONTROL_TIME = 105000; // 105,000 ms / 105 s / 1m45s
int TEN_SECONDS_LEFT =  OPCONTROL_TIME - 10000;     // 95,000 ms
int THREE_SECONDS_LEFT = OPCONTROL_TIME - 3000; 	// 102,000 ms