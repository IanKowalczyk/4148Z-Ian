#include "lib_header/robot_h/util.h"
// #include <cmath>

// // Math constants (why doesn't cmath work??)
// double M_PI = 3.14159265358979323846;

// // ******** Conversion Rates ******** //
// double PCT_TO_VOLT = 127 / 100;
// double VOLT_TO_PCT = 100 / 127;

// double RAD_TO_DEG = 180 / M_PI;
// double DEG_TO_RAD = M_PI / 180;

// /** OLD 2.75 in converstion ratios */
// double DRIVE_INCH_TO_DEG_275 = 360 / (2.75 * M_PI);
// double DRIVE_DEG_TO_INCH_275 = (2.75 * M_PI) / 360;

// /** THEORETICAL 2.00 in conversion ratios */
// double DRIVE_INCH_TO_DEG_2IN = 360 / (2.00 * M_PI); // 57.29577
// double DRIVE_DEG_TO_INCH_2IN = (2.00 * M_PI) / 360; // 0.017453 

// /** NEW / OBSERVED 2.00 in conversion ratios */
// // double DRIVE_INCH_TO_DEG_2IN = 56.25;           // (1350 / 24) ~ 56.25 (don't use in this form)
// // double DRIVE_DEG_TO_INCH_2IN = 0.0177777777;    // (24 / 1350) ~ 0.01777777 (don't use in this form)


// **** Debug **** //
// void debugBox(color, int x1, int y1, int x2, int y2) {

// }

// **** Match timer **** //
void matchTimerRumble(int startTime) {
    static int rumbleCount = 0;
    if(pros::c::millis() - startTime >= TEN_SECONDS_LEFT && pros::c::millis() - startTime < 110000) {
			// rumble once every second at last 10 seconds
			if(rumbleCount % 1000 == 0) {controller.rumble(".");}

			// rumble twice every second at last 3 seconds
			if(pros::c::millis() - startTime >= THREE_SECONDS_LEFT) {
				if(rumbleCount % 500 == 0) {controller.rumble(".");}
			}
			rumbleCount += 20;
	}
}

// ******** Util Functions ******** //

double wheelDegreeToInch(double diameter) {
    return (M_PI * diameter) / 360;
}
double wheelInchToDegree(double diameter) {
    return 1 / wheelDegreeToInch(diameter);
}

double constrainValue(double input, double max, double min) {
    if(input > max) {input = max;}
    if(input < min) {input = min;}
    return(input);
}
double constrainVoltage(int input, int max, int min) {
    if(input > max) {input = max;}
    if(input < min) {input = min;}
    return(input);
}

double constrainAngle360(double input) {
    while(!(input >= 0 && input < 360)) {
        if(input < 0) { input += 360; }
        if(input >= 360) { input -= 360; }
    }
    return(input);
}

double constrainAngle180(double input) {
    while(!(input >= -180 && input < 180)) {
        if(input < -180) { input += 360; }
        if(input >= 180) { input -= 360; }
    }
    return(input);
}

double constrainAngle90(double input) {
    while(!(input >= -90 && input < 90)) {
        if(input < -90) { input += 180; }
        if(input >= 90) { input -= 180; }
    }
    return(input);
}

double getSign(double input) {
    return(std::fabs(input) / input);
}

double dAverage(std::vector<double> inputs) {
    double sum = 0;
    for(int i = 0; i < inputs.size(); i++) {
        sum += inputs[i];
    }
    return(sum / inputs.size());
}

