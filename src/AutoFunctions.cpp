#include "main.h"
#include "Headers/AutoFunctions.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Motors.hpp"
#include "Headers/Functions.hpp"

//function that holds the motor position
void brake()
{
    LFront.move_velocity(0);
    RFront.move_velocity(0);
    LBack.move_velocity(0);
    RBack.move_velocity(0);
    LFront.set_brake_mode(MOTOR_BRAKE_HOLD);
    RFront.set_brake_mode(MOTOR_BRAKE_HOLD);
    LBack.set_brake_mode(MOTOR_BRAKE_HOLD);
    RBack.set_brake_mode(MOTOR_BRAKE_HOLD);
}

//function that returns the power that should be sent to the base motors to get to the target x-coordinate
int driveFB(double target, int maxVel, int minVel)
{
    error_Y = target - ycoord;

    P_Y = error_Y * kP_Y;
    D_Y = (error_Y - lastError_Y) * kD_Y;
    lastError_Y = error_Y;

    pwr_Y = P_Y + D_Y;

    //overrides power if it is too high or too low or if target has been reached
    fabs(error_Y) <= 0.25 ? pwr_Y = 0 : pwr_Y > maxVel ? pwr_Y = maxVel : pwr_Y < minVel ? pwr_Y = minVel : pwr_Y = pwr_Y;

    return pwr_Y;//returns the pwr to function call
}

//function that returns the power that should be sent to the base motors to get to the target y-coordinate
int driveLR(double target, int maxVel, int minVel)
{
    error_X = target - xcoord;

    P_X = error_X * kP_X;
    D_X = (error_X - lastError_X) * kD_X;
    lastError_X = error_X;

    pwr_X = P_X + D_X;

    //overrides power if it is too high or too low or if target has been reached
    fabs(error_X) <= 0.25 ? pwr_X = 0 : pwr_X > maxVel ? pwr_X = maxVel : pwr_X < minVel ? pwr_X = minVel : pwr_X = pwr_X;

    return pwr_X;//returns the pwr to function call
}

//function that returns the power that should be sent to the base motors to get to the target angle
int driveRot(double target, int maxVel, int minVel)
{
    error_A = target - global_angle;

    P_A = error_A * kP_A;
    D_A = (error_A - lastError_A) * kD_A;
    lastError_A = error_A;

    pwr_A = P_A + D_A;

    //overrides power if it is too high or too low or if target has been reached
    fabs(error_A) <= degToRad(0.25) ? pwr_A = 0 : pwr_A > maxVel ? pwr_A = maxVel : pwr_A < minVel ? pwr_A = minVel : pwr_A = pwr_A;

    return pwr_A;//returns the pwr to function call
}

//function that uses x,y and angle correction functions above to set motor power until all 3 motions have settled
void autoDrive(double x, double y, double a, int maxVelRot, int minVelRot, int maxVel, int minVel)
{
    do
    {
        power = driveFB(y, maxVel, minVel);//sets forward/back translation to the pwr returned
        strafe = driveLR(x, maxVel, minVel);//sets left/right translation to the pwr returned
        turn = driveRot(a, maxVelRot, minVelRot);//sets rotation to the pwr return
        moveBase(power, strafe, turn);//sends power to the base motors after function calls

        pros::delay(5);
    }while(fabs(error_X) >= 0.25 && fabs(error_Y) >= 0.25 && fabs(error_A) >= degToRad(0.25));//stops looping when all translations and rotations are settled
    brake();//holds the motor positions
}
