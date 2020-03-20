#include "main.h"
#include "Headers/Motors.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Functions.hpp"
#include "Headers/Autonomous.hpp"
#include <iostream>

enum trayPositions {stopTray, low, score};
trayPositions trayPos = low;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::Task updateTask(update);
	pros::Task printTask(print);
    pros::Task driveTask(drive);
    pros::Task intakeTask(intake);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
    red15();
}

// pros::vision_signature_s_t GREEN_CUBE (1, -7419, -5305, -6362, -3343, -1655, -2499, 3.000);
// pros::vision_signature_s_t ORANGE_CUBE (2, 7349, 9591, 8470, -2817, -2127, -2472, 3.000);
// pros::vision_signature_s_t PURPLE_CUBE (3, 43, 1365, 704, 8749, 11941, 10345, 3.100);

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol()
{
	while (true)
    {
        power = (master.get_analog(ANALOG_LEFT_Y) * (200.0/127.0));//forward back movement mapped to 200rpm
        turn = (master.get_analog(ANALOG_RIGHT_X) * (200.0/127.0) * 0.5);//left right straffing movement mapped to 200rpm
        strafe = (master.get_analog(ANALOG_LEFT_X) * (200.0/127.0));//rotational movement mapped to 200rpm
        if(abs(strafe) < 20) strafe = 0;

        if(master.get_digital(DIGITAL_L1)) intakePow = 200;//intake full power
        else if(master.get_digital(DIGITAL_L2)) intakePow = -100;//outtake half power
        else if(master.get_digital(DIGITAL_A)) intakePow = -50;
        else if(master.get_digital(DIGITAL_LEFT)) intakePow = -200;//outtake full power
        else intakePow = 0;

        if(master.get_digital(DIGITAL_DOWN)) trayPos = low;//sets custom variable to low position
        else if (master.get_digital(DIGITAL_UP)) trayPos = score;//sets custom variable to score position

        if(abs(master.get_analog(ANALOG_RIGHT_Y)) > 20)
        {
            arm1.move(master.get_analog(ANALOG_RIGHT_Y));
            arm1.move(master.get_analog(ANALOG_RIGHT_Y));
        }
		pros::delay(20);
	}
}
