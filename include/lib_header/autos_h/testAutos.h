#ifndef TEST_AUTOS_H
#define TEST_AUTOS_H
#include "main.h"
#include "lib_header/api/motion_api.h"
#include "lib_header/api/robot_api.h"
#include "lib_header/api/subsystems_api.h"
#include "lib_header/api/control_api.h"

// ******* Test Autos *******//
/** @brief Tests robot subsystems: intake, wings, cata */
extern void autoFunctionTest();

// Odom tests
extern void odomBoxTest();
extern void slowOdomBoxTest();
extern void odomTriangleTest();

// Squiggles
extern void squigglesTest();
extern void chainedMoveToPointTest();

// Curves
extern void oldCurveTest();
extern void curveTuning();

#endif