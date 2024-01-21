#pragma once

// **** Include this file (lib_header/api.h) in main.h **** //

// auto_h
#include "lib_header/auto_h/autoselector.h"
#include "lib_header/auto_h/motion.h"
#include "lib_header/auto_h/odom.h"
#include "lib_header/auto_h/pid.h"

// robot_h
#include "lib_header/robot_h/robotStates.h"
#include "lib_header/robot_h/robot_config.h"

// subsystems_h
#include "lib_header/subsystems_h/shooter.h"
#include "lib_header/subsystems_h/drive.h"
#include "lib_header/subsystems_h/intake.h"
#include "lib_header/subsystems_h/misc.h"

// other files
#include "lib_header/autos.h"
#include "lib_header/gui.h"
#include "lib_header/util.h"