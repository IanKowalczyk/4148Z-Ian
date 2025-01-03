#ifndef ODOM_H
#define ODOM_H
#include "main.h"


/**
 * @brief Class that creates a point with x, y coordinates and an orientation
*/
class Point {
    private:
    public:
    double x;
    double y;
    double theta;
    
    // double getX() {return(x);}
    // double getY() {return(y);}
    // double getTheta() {return(theta);}

    Point() {};
    Point(double point_x, double point_y) {
        x = point_x;
        y = point_y;
        // theta = point_heading;
    }
    
    /**
     * @brief Sets the coordinates of the point 
     * @param new_x New x coordinate
     * @param new_y New y coordinate
     * @param new_theta New orientation in degrees
    */
    void setPoint(double new_x, double new_y, double new_theta);

    /**
     * @brief Sets x, y, and theta to 0
    */
    void reset() {
        x = y = theta = 0.0;
    }
};

// Points 
extern Point globalPose;
extern Point localPose;
extern Point deltaPose;

/**
 * @brief Updates the robot's position
 */
extern void updatePosition();

/** 
 * @brief Resets the sensors used to track position
 */
extern void resetOdomSensors();


#endif