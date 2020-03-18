#include "main.h"
#include "Headers/Motors.hpp"
#include "Headers/Functions.hpp"
#include "Headers/Variables.hpp"
#include "Headers/Sensors.hpp"

//passes a degree and converts it to a radian
double degToRad(double degrees){return degrees/180 *M_PI;}

//passes a radian and converts it to a degree
double radToDeg(double radians){return radians/M_PI *180;}

//passes inchs and converts it to encoder ticks bassed on the wheel diameter on the tracking wheels
double inchToTick(double inch){return (inch * (wheelSize*M_PI)) * 360;}

//passes a real number and returns the sign
int sgn(double num) {return (num < 0 ? -1 : num > 0 ? 1 : 0);}

void moveBase(int power, int strafe, int turn)
{
    LFront.move_velocity(power + turn + strafe);
    LBack.move_velocity(power + turn - strafe);
    RFront.move_velocity(power - turn - strafe);
    RBack.move_velocity(power - turn + strafe);
}

//updates all tracking based variables each memory cycle
void update(void*)
{
    double radiusR = 0;
    double radiusB = 0;
    double h = 0;
    double h2 = 0;
    double theta = 0; double beta = 0; double alpha = 0;
    double Xx = 0; double Xy = 0; double Yx = 0; double Yy = 0;

    LeftTracker.reset(); RightTracker.reset(); BackTracker.reset();
    double newleft = 0; double newright = 0; double newback = 0;
    double Right = 0; double Left = 0; double Back = 0;
    double lastleft = 0, lastright = 0, lastback = 0;

    while (true)
    {
        //amount encoders moved (radians)
	    newleft = LeftTracker.get_value() / 360.0 * (wheelSize * M_PI);//number of radians the left encoder moved
	    newright = RightTracker.get_value() / 360.0 * (wheelSize * M_PI);//number of radians the right encoder moved
        newback = BackTracker.get_value() / 360.0 * (wheelSize * M_PI);//number of radians the rear encoder moved
        Right = newright - lastright;//the delta of the right encoder
        Left = newleft - lastleft;//the delta of the left encoder
        Back = newback - lastback;//the delta of the rear encoder

        //update last values
	    lastright = newright;
	    lastleft = newleft;
	    lastback = newback;
	    theta = (Left - Right) / distance_LR;//angle of the bot in radians

        //if robot turned in any direction
	    if (theta != 0)
        {
		    radiusR = Right / theta;
            beta = theta / 2.0;
		    h = (radiusR + distance_LR / 2) * 2 * sin(beta);
		    radiusB = Back / theta;
		    h2 = (radiusB + distance_B) * 2 * sin(beta);
	    }

        //if robot moved straight or didn't move
	    else
        {
		    h = Right;
		    h2 = Back;
		    beta = 0;
	    }
		alpha = global_angle + beta;

        //update global x, y and angle
		Xx = h2 * cos(alpha);
		Xy = h2 * -sin(alpha);
		Yx = h * sin(alpha);
		Yy = h * cos(alpha);
		xcoord += Yx + Xx;
		ycoord += Yy + Xy;
        global_angle += theta;

      pros::delay(5);
    }
}

void print(void*)
{
    pros::lcd::initialize();//initialize the lcd on the brain
    while(!pros::lcd::is_initialized()){pros::delay(1);}//wait until lcd is initialized
    int target = pros::millis() + 5000, count = 0;//set target time to 15 seconds into the future
    while(true)
    {
        pros::lcd::print(0, "tPot:%d, aPot:%d\n", trayPot.get_value_calibrated(), armPot.get_value_calibrated());
        pros::lcd::print(1, "X:%f, Y:%f, A:%f\n", xcoord, ycoord, radToDeg(global_angle));
        //print potentiometer values and coordinate location and angle of the bot
        if(target <= pros::millis())
        {
          target += 5000;//updates target
          count++;//increases count
        }

        if(count % 2 == 0)//if count is an even number display motor temperatures
        {
            pros::lcd::print(2, "B:LF:%dc, RF:%dc, LB:%dc, RB:%dc\n",
                LFront.get_temperature(), RFront.get_temperature(), LBack.get_temperature(), RBack.get_temperature());
            pros::lcd::print(3, "I:LF:%dc, RF:%dc, LB:%dc, RB:%dc\n",
                LFIntake.get_temperature(), RFIntake.get_temperature(), LBIntake.get_temperature(), RBIntake.get_temperature());
            pros::lcd::print(4, "Arm:L:%dc, R:%dc Tilt:L:%dc, R:%dc",
                arm1.get_temperature(), arm2.get_temperature(), tilter1.get_temperature(), tilter2.get_temperature());
        }
        else//if count is odd display current draw of the motors
        {
            pros::lcd::print(2, "B:LF:%dA, RF:%dA, LB:%dA, RB:%dA\n",
                LFront.get_current_draw(), RFront.get_current_draw(), LBack.get_current_draw(), RBack.get_current_draw());
            pros::lcd::print(3, "I:LF:%dA, RF:%dA, LB:%dA, RB:%dA\n",
                LFIntake.get_current_draw(), RFIntake.get_current_draw(), LBIntake.get_current_draw(), RBIntake.get_current_draw());
            pros::lcd::print(4, "Arm:L:%dA, R:%dA Tilt:L:%dA, R:%dA",
                arm1.get_current_draw(), arm2.get_current_draw(), tilter1.get_current_draw(), tilter2.get_current_draw());
        }
        pros::delay(10);
    }
}

void drive(void*)
{
    while(true)
    {
        moveBase(power, strafe, turn);//move base motors according to controller input
        pros::delay(10);
    }
}

//task that sets the intake motor power based on button inputs
void intake(void*)
{
    while(true)
    {
        RFIntake.move_velocity(intakePow);
        LFIntake.move_velocity(intakePow);
        RBIntake.move_velocity(intakePow);
        LBIntake.move_velocity(intakePow);

        pros::delay(10);
    }
}
