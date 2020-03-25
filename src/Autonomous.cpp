#include "main.h"
#include "Headers/Autonomous.hpp"
#include "Headers/Motors.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Functions.hpp"
#include "Headers/AutoFunctions.hpp"

void test(double target, int maxVel, int minVel)
{
    do
    {
        pros::lcd::print(0, "target: %d\terror: %d", target, error_Y);
        moveBase(driveFB(target, maxVel, minVel));

        pros::delay(5);
    }while(fabs(error_Y) > 0.25);
    brake();
}
void red15()
{
    test(24, 200, 20);
    // while(true)
    // {
    // moveBase(0, 200, 0);
    // }
}
