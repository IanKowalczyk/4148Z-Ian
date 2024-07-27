#ifndef MATCH_AUTOS_H
#define MATCH_AUTOS_H
#include "main.h"
#include "lib_header/api/motion_api.h"
#include "lib_header/api/robot_api.h"
#include "lib_header/api/subsystems_api.h"
#include "lib_header/api/control_api.h"


// ******** Current Autos ******** //
extern void defenseWP();
extern void defenseElims();
extern void sixBallWP();
extern void sixBallElims();

// ******** Old Autos ******** //
enum class defense_auto_mode{FOUR_BALL, THREE_BALL};
enum class offense_auto_mode{SAFE, RISKY};
enum class sixBall_mode{BAR, MID};

extern void newSixBall(sixBall_mode s);

/** @brief Setup: Right side of Matchload Station, 45 deg -- Shoot preload; Score 2 from auto line;
 * (SOLO) Knock out matchload triball; Touch Hang Bar -- OR -- (ELIMS)  Drive back to Matchload Station */
extern void defenseAuto(defense_auto_mode s);

/** @brief Setup: In front of Matchload station, facing goal, 0 deg -- Push preload into goal; Score 1 from mid;
 *  (SAFE) Drive to Hang Bar and intake triball -- OR -- (RISKY) Score 2 from auto line */
extern void offenseAuto(offense_auto_mode s);

/** @brief Setup: Top right corner of tile next to matchload, preload in line with HIM sticker --
 * Shoot preload, (turn) intake hangBarTriball, shoot to goal; Knock out Matchload triball & push into goal; Score 1 from mid and 2 from auto line */
extern void sixBall(sixBall_mode s);

/** @brief Setup: In front of matchload station, back to goal, 200 deg --
 * Push preload into goal; Score 1 from mid and 2 from auto line */
extern void fourBall();


#endif