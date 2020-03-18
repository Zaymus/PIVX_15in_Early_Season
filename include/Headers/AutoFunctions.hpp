#include "main.h"
#include "Variables.hpp"

#ifndef AUTOFUNCTIONS_HPP
#define AUTOFUNCTIONS_HPP

extern int driveFB(double target, int maxVel = 142, int minVel = 24);
extern int driveLR(double target, int maxVel = 142, int minVel = 24);
extern int driveRot(double target, int maxVel = 70, int minVel = 15);
extern void autoDrive(double x = xcoord, double y = ycoord, double a = global_angle, int maxVelRot = 70, int minVelRot = 15, int maxVel = 142, int minVel = 24);
extern void brake();

#endif
