#include "lib_header/control_h/odom.h"

// Points 
Point globalPose;
Point localPose;
Point deltaPose;

void Point::setPoint(double new_x, double new_y, double new_theta) {
    x = new_x;
    y = new_y;
    theta = new_theta;
    inertial.set_heading(new_theta);
}

// odom variables //
double frontEncValue;
double lastFrontEncValue;
double deltaFrontEncValue;
double lastHeading;
double sideEncValue;
double lastSideEncValue;
double deltaSideEncValue;
double polarAngle;
double polarLength;
double finalPolarAngle;

void updatePosition() {
    // resetOdomSensors();

    // while(true) {
    // Update front encoder in inches
    frontEncValue = (frontEnc.get_position() / 100)* wheelDegreeToInch(TRACKING_WHEEL_DIAMETER); // (2.75 * M_PI) / 360
    deltaFrontEncValue = frontEncValue - lastFrontEncValue;
    
    // Update side encoder in inches
    sideEncValue = (sideEnc.get_position() / 100) * wheelDegreeToInch(TRACKING_WHEEL_DIAMETER);
    // sideEncValue = 0;
    deltaSideEncValue = sideEncValue - lastSideEncValue;

    // Update global theta in radians
    globalPose.theta = inertial.get_heading() * DEG_TO_RAD;
    deltaPose.theta = globalPose.theta - lastHeading;

    // Update previous values
    lastFrontEncValue = frontEncValue;
    lastSideEncValue = sideEncValue;
    lastHeading = globalPose.theta;

    // Calculate local x and y, using chord length as Y-axis
    if(deltaPose.theta == 0) {
        localPose.x = deltaSideEncValue;
        localPose.y = deltaFrontEncValue;
    }
    else {
        localPose.x = (2 * sin(deltaPose.theta / 2)) * ((deltaSideEncValue / deltaPose.theta) + SIDE_ENC_OFFSET);
        localPose.y = (2 * sin(deltaPose.theta / 2)) * ((deltaFrontEncValue / deltaPose.theta) + FRONT_ENC_OFFSET);
    }

    // Convert local x,y to polar coordinate
    if(localPose.x == 0 && localPose.y == 0) {
        polarAngle = 0;
        polarLength = 0;
    }
    else {
        polarAngle = atan2(localPose.y, localPose.x);
        polarLength = sqrt(pow(localPose.x, 2) + pow(localPose.y, 2));
    }

    // Rotate polar coordinate by lastHeading + deltaTheta/2
    finalPolarAngle = polarAngle - lastHeading  - (deltaPose.theta / 2);

    // Recalculate change in x and y
    deltaPose.x = polarLength * cos(finalPolarAngle);
    deltaPose.y = polarLength * sin(finalPolarAngle);

    // Update global position
    globalPose.x += deltaPose.x;
    globalPose.y += deltaPose.y;

    pros::screen::erase_line(0, 0, 200, 1);
    pros::screen::print(TEXT_MEDIUM_CENTER, 0, "x: %3.2f, y: %3.2f, theta: %3.2f", globalPose.x, globalPose.y, globalPose.theta*RAD_TO_DEG);

    // pros::delay(20);
    // }
}

void resetOdomSensors() {
    frontEnc.reset_position();
    sideEnc.reset_position();
}