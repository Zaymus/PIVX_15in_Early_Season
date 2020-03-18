#include "main.h"
#include "Headers/Autonomous.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Functions.hpp"
#include "Headers/AutoFunctions.hpp"

int maxVel = 200, minVel = 0;
void test(double target)
{
    do
    {
        moveBase(int(driveFB(target, maxVel, minVel)), 0, 0);

    }while(fabs(error_Y) > 0.25);
    brake();
}
void red15()
{
    test(24);
    // while(true)
    // {
    // moveBase(0, 200, 0);
    // }
}
