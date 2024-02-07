#ifndef AUTOS_H
#define AUTOS_H
#include "main.h"

extern int autoToRun;

// ******** Auto Functions ******** //
extern void releaseIntake();

// ******* Test Autos *******//
/** @brief Tests robot subsystems: intake, wings, cata */
extern void autoFunctionTest();

// Odom tests
extern void odomBoxTest();
extern void slowOdomBoxTest();
extern void odomTriangleTest();

// Squiggles
extern void squigglesTest();
extern void chainedMoveToPoint();

// Curves
extern void oldCurveTest();
extern void curveTuning();

/** @brief Parameter for defenseAuto */
enum class defense_auto_mode{FOUR_BALL, THREE_BALL};
enum class offense_auto_mode{SAFE, RISKY};
enum class sixBall_mode{BAR, MID};
// enum progSkills_mode{LEFT, RIGHT};

extern void newSixBall(sixBall_mode s);

// ******* Match Autos *******//
/** @brief Setup: Right side of Matchload Station, 45 deg -- Shoot preload; Score 2 from auto line;
 * 
 * (SOLO) Knock out matchload triball; Touch Hang Bar -- OR -- (ELIMS)  Drive back to Matchload Station
*/
extern void defenseAuto(defense_auto_mode s);

/** @brief Setup: In front of Matchload station, facing goal, 0 deg -- Push preload into goal; Score 1 from mid;
 * 
 *  (SAFE) Drive to Hang Bar and intake triball -- OR -- (RISKY) Score 2 from auto line
*/
extern void offenseAuto(offense_auto_mode s);

/** @brief Setup: Top right corner of tile next to matchload, preload in line with HIM sticker --
 * 
 * Shoot preload, (turn) intake hangBarTriball, shoot to goal; Knock out Matchload triball & push into goal; Score 1 from mid and 2 from auto line
*/
extern void sixBall(sixBall_mode s);

/** @brief Setup: In front of matchload station, back to goal, 200 deg --
 * 
 * Push preload into goal; Score 1 from mid and 2 from auto line
*/
extern void fourBall();

extern void defenseSafe();

/** @brief Setup: Right side of Matchload Station, 45 deg --
 * 
 * Shoot preloads (44 + 4 [error margin]); move across to other zone; push triballs into goal
*/
extern void progSkills();

extern void progFirstHalf();


#endif