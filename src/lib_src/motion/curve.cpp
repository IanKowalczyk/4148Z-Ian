#include "lib_header/motion_h/curve.h"

// ******** Variables ******** //
double radius;


// ******** Function ******** //
// void curve() {
//     int startTime = pros::c::millis();

//     int stepCount = 50;
//     double angleError = turn_target - inertial.get_heading();  // calculate error to endAngle

//     double arcLength = 2 * M_PI * radius * (std::fabs(angleError) / 360); // use error to endAngle to find arc length to travel
   
//     double arcLengthStep = arcLength / stepCount;   // define step for arclength
//     double tempArcLength = arcLengthStep;           // will be used to check when to iterate angle

//     double angleStep = angleError / stepCount;      // define step for angle
//     double tempAngle = inertial.get_heading() + angleStep;  // used to get arc started

//     double driveError, turnError;
//     double drivePower, turnPower;
//     double currentPosition = (frontEnc.get_position() / 100) * DRIVE_DEG_TO_INCH_2IN;
    
//     while(true) {
//         driveError = 
//         pros::delay(10);
//     }
// }


// ******** Setters ******** //
void setCurve(double distance, double endAngle, double radius, int maxDrivePower, int maxTurnPower, int maxTime) {
    int stepCount = 50; // How many "slices" to divide the arc into

    double angleError = endAngle - inertial.get_heading();  // calculate error to endAngle
    double arcLength = 2 * M_PI * radius * (std::fabs(angleError) / 360); // use error to endAngle to find arc length to travel

    double arcLengthStep = arcLength / stepCount;   // define step for arclength
    double tempArcLength = arcLengthStep;           // will be used to check when to iterate angle

    double angleStep = angleError / stepCount;      // define step for angle
    double tempAngle = inertial.get_heading() + angleStep;  // used to get arc started

//  * returnSign(angleError)
    setMove(arcLength + distance, tempAngle, maxDrivePower, maxTurnPower, maxTime, false, false, false); // arcLength + distance
    
    for(int i = 0; i < stepCount - 1; i++) {    // step count - 2, so that we have time to add distance after arc before exiting move function
        while(drive_position < tempArcLength) {
            pros::delay(1);
        }
		turn_target += angleStep;
        tempArcLength += arcLengthStep;
        if(tempArcLength > arcLength) {tempArcLength = arcLength;}
		pros::delay(5);
	}
    turn_target = endAngle;
}


// ******** Chained Setters ******** //