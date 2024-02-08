#ifndef DRIVER_CPP
#define DRIVER_CPP

#include "main.h"
#include "../include/driver.h"
#include "pid.h"

bool wingsTog = false;
bool elevationTog = false;
bool hookTog = false;
bool blockerTog = false;

void arcade_driverSixMotor(){
    int power = -(master.get_analog(ANALOG_LEFT_Y));
	int turn = -(master.get_analog(ANALOG_RIGHT_X))*.90;
	int left = power + turn;
	int right = power - turn;
	LF.move(left);
	LM.move(left);
	LB.move(left);
	RF.move(right);
	RM.move(right);
	RB.move(right);
}

void intake_driver(){
    if (master.get_digital(DIGITAL_R1)){
		intake.move_velocity(200);
	}
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
		intake.move_velocity(-200);
	}
    else{
		intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		intake.brake();
	}
}

void wings_driver(){
    if (master.get_digital_new_press(DIGITAL_L1)){
		wingsTog = !wingsTog;
	    if (wingsTog){
		    wings.set_value(HIGH);
		}
	    else{
		    wings.set_value(LOW);
		}
	}
}

void hook_driver(){
    if (master.get_digital_new_press(DIGITAL_A)){
		hookTog = !hookTog;
		if (hookTog){
			hook.set_value(HIGH);
		}
		else{
			hook.set_value(LOW);
		}
	}
}

void elevation_driver(){
    if (master.get_digital_new_press(DIGITAL_X)){
		elevationTog = !elevationTog;
		if (elevationTog){
			elevation.set_value(HIGH);
		}
		else{
			elevation.set_value(LOW);
		}
	}
}

void blocker_driver(){
    if (master.get_digital_new_press(DIGITAL_LEFT)){
		blockerTog = !blockerTog;
		if (blockerTog){
			blocker.set_value(HIGH);
		}
		else{
			blocker.set_value(LOW);
		}
	}
}

/*
void kicker_driver(){
    if (kickerLimit.get_value() == false || master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
		K.move_velocity(85);
	}
    else{
		K.brake();
	}
}
*/

void kicker_driver(){
    if (master.get_digital(DIGITAL_L2)){
		K.move_velocity(170); //200
	}
    else{
		K.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		K.brake();
	}
}


#endif