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
        autoDrive(0, 0, 90);
        pros::delay(5);
    }while(fabs(error_Y) > 0.20);
    brake();
}
void red15()
{
    autoDrive(0, 0, 90);
}
