#ifndef DRIVER_CONTROL
#define DRIVER_CONTROL

#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robot.h"
#include <cmath>
#include <ios>

void chassis(){
	RF.move(con.get_analog(ANALOG_RIGHT_Y));
    RB.move(con.get_analog(ANALOG_RIGHT_Y));

    LF.move(con.get_analog(ANALOG_LEFT_Y)); 
    LB.move(con.get_analog(ANALOG_LEFT_Y));
}

void intake(){
    if(con.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        intakeL.move(-600); 
        intakeR.move(-600); 
    }
}



#endif
