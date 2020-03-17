#include "main.h"

#ifndef AUTOFUNCTIONS_HPP
#define AUTOFUNCTIONS_HPP

extern int driveFB(double target, int maxVel, int minVel);
extern int driveLR(double target, int maxVel, int minVel);
extern int driveRot(double target, int maxVel, int minVel);
extern void autoDrive(double x, double y, double a, int maxVelRot = 70, int minVelRot = 15, int maxVel = 142, int minVel = 24);
extern void brake();

#endif
