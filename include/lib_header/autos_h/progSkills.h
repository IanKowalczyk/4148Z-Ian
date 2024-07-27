#ifndef PROG_SKILLS_H
#define PROG_SKILLS_H
#include "main.h"
#include "lib_header/api/motion_api.h"
#include "lib_header/api/robot_api.h"
#include "lib_header/api/subsystems_api.h"
#include "lib_header/api/control_api.h"

// ******** Prog Skills ******** //
/** @brief Setup: Right side of Matchload Station, 45 deg --
 * Shoot preloads (44 + 4 [error margin]); move across to other zone; push triballs into goal
*/
extern void progSkills(); // old
extern void newProgSkillsRLM();

// actual prog
extern void newProgSkillsMRL();

// driver macro
extern void progFirstHalf();

#endif