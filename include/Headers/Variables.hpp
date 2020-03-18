#include "main.h"

#ifndef VARIABLES_HPP
#define VARIABLES_HPP

extern pros::Controller master;

extern int power, strafe, turn, intakePow;
extern double kP_X, kD_X, P_X, D_X, pwr_X, error_X, lastError_X;
extern double kP_Y, kD_Y, P_Y, D_Y, pwr_Y, error_Y, lastError_Y;
extern double kP_A, kD_A, P_A, D_A, pwr_A, error_A, lastError_A;

extern double wheelSize, distance_LR, distance_B, xcoord, ycoord, global_angle;

#endif
