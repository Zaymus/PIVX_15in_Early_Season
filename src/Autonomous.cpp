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
        error_A = target - global_angle;

        P_A = error_A * kP_A;
        D_A = (error_A - lastError_A) * kD_A;
        lastError_A = error_A;

        pwr_A = P_A + D_A;

        //overrides power if it is too high or too low or if target has been reached
        fabs(error_A) <= degToRad(0.25) ? pwr_A = 0 : pwr_A > maxVel ? pwr_A = maxVel : pwr_A < minVel ? pwr_A = minVel : pwr_A = pwr_A;
        moveBase(0, 0, pwr_A);
    }while(fabs(error_A > degToRad(0.25)));
    brake();
}

void red15()
{
    //autoDrive(0, 0, 90);
    //pros::lcd::initialize();
    test(90, 70, 15);
}
