#include "main.h"
#include "Headers/Autonomous.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Functions.hpp"
#include "Headers/AutoFunctions.hpp"
double kP_X = 10, kD_X = 0, P_X = 0, D_X = 0, pwr_X = 0, error_X = 0, lastError_X = 0;
int maxVel = 200, minVel = 0;
void test(double target)
{
    do
    {
        error_X = target - xcoord;
        totalError_X += error_X;

        P_X = error_X * kP_X;
        D_X = (error_X - lastError_X) * kD_X;
        lastError_X = error_X;

        pwr_X = P_X + D_X;

        //overrides power if it is too high or too low
        if(pwr_X > maxVel){ pwr_X = maxVel;}
        else if (pwr_X < minVel){pwr_X = minVel;}

    }while(!(error_X < 0.25 && error_X > 0.25));
    brake();
}
void red15()
{
    //test(90);
    while(true)
    {
    moveBase(200, 0, 0);
    }
}
