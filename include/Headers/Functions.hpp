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
extern void moveBase(int y = 0, int x = 0, int a = 0);

extern void update(void*);
extern void print(void*);
extern void drive(void*);
extern void intake(void*);
// extern void tiltTo(trayPositions trayPos);
// extern void tray(void*);
// extern void arm(void*);

#endif
