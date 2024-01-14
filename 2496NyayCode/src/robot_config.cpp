#ifndef ROBOT_CONFIG_CPP
#define ROBOT_CONFIG_CPP

#include "main.h"
#include "../include/robot_config.h"
#include "pros/adi.hpp"

//CHASSIS MOTORS
pros::Motor LF (4); //"false" one side to reverse
pros::Motor LB (13);
pros::Motor LM (1);
pros::Motor RF (9, true);
pros::Motor RB (19, true);
pros::Motor RM (20, true);

//KICKER MOTORS
pros::Motor K (12, true);

//INTAKE MOTORS
pros::Motor intake (10,true); 

//CONTROLLER
pros::Controller master (CONTROLLER_MASTER);

//SOLENOIDS
pros::ADIDigitalOut wings ('D', false);
pros::ADIDigitalOut descorer ('H', true);
pros::ADIDigitalOut hook ('C');
pros::ADIDigitalOut blocker('E', true);
	
//LIMIT SWITCH
pros::ADIDigitalIn kickerLimit ('B');

//IMU
pros::IMU imu (16); 

#endif 