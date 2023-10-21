#ifndef ROBOT_CONFIG_CPP
#define ROBOT_CONFIG_CPP

#include "main.h"
#include "../include/robot_config.h"
#include "pros/adi.hpp"

//CHASSIS MOTORS
pros::Motor LF (9); //"false" one side to reverse
pros::Motor LB (18);
pros::Motor RF (13, true);
pros::Motor RB (12, true);

//KICKER MOTORS
pros::Motor KL (19);
pros::Motor KR (20, true);

//INTAKE MOTORS
pros::Motor intake (11); //"true" one of these to reverse

//CONTROLLER
pros::Controller master (CONTROLLER_MASTER);

//SOLENOIDS
pros::ADIDigitalOut wings ('G', true);
pros::ADIDigitalOut descorer ('H', true);
pros::ADIDigitalOut hook ('D');
pros::ADIDigitalOut blocker('E', true);
	
//LIMIT SWITCH
pros::ADIDigitalIn kickerLimit ('B');

//IMU
pros::IMU imu (16); 

#endif