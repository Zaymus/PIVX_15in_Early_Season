#include "main.h"
#include "Headers/Motors.hpp"

//dead ports: 2, 3, 11
pros::Motor RFront(17, MOTOR_GEARSET_18, true);
pros::Motor RBack(18, MOTOR_GEARSET_18, true);
pros::Motor LFront(15, MOTOR_GEARSET_18, false);
pros::Motor LBack(14, MOTOR_GEARSET_18, false);

pros::Motor RBIntake(10, MOTOR_GEARSET_18, true);
pros::Motor RFIntake(9, MOTOR_GEARSET_18, true);
pros::Motor LBIntake(12, MOTOR_GEARSET_18, false);
pros::Motor LFIntake(4, MOTOR_GEARSET_18, false);

pros::Motor arm1(1, MOTOR_GEARSET_36, false);
pros::Motor arm2(20, MOTOR_GEARSET_36, true);

pros::Motor tilter1(8, MOTOR_GEARSET_36, true);
pros::Motor tilter2(13, MOTOR_GEARSET_36, false);
