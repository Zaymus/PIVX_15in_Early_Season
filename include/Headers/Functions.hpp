#include "main.h"
// #include "Variables.hpp"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

// extern void setLimits();
// extern void checkLimits();

extern double degToRad(double degrees);
extern double radToDeg(double radians);
extern double inchToTick(double inch);
extern int sgn(double num);
extern void moveBase(int power = 0, int strafe = 0, int turn = 0);

extern void update(void*);
extern void print(void*);
extern void drive(void*);
extern void intake(void*);
// extern void tiltTo(trayPositions trayPos);
// extern void tray(void*);
// extern void arm(void*);

#endif
