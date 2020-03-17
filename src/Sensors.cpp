#include "main.h"
#include "Headers/Sensors.hpp"

pros::ADIPotentiometer trayPot(7);
pros::ADIPotentiometer armPot(8);

pros::ADIEncoder RightTracker(1, 2, false);
pros::ADIEncoder BackTracker(3, 4, false);
pros::ADIEncoder LeftTracker(5, 6, true);

//pros::ADILineSensor goalzone('G');
