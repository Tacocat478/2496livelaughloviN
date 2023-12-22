#ifndef ROBOT_CONFIG_CPP
#define ROBOT_CONFIG_CPP

#include "main.h"
#include "../include/robot_config.h"
#include "pros/adi.hpp"

//CHASSIS MOTORS
pros::Motor LF (11); //"false" one side to reverse
pros::Motor LB (13);
pros::Motor LM (12);
pros::Motor RF (1, true);
pros::Motor RB (4, true);
pros::Motor RM (2, true);

//KICKER MOTORS
pros::Motor KL (19);
pros::Motor KR (20, true);

//INTAKE MOTORS
pros::Motor intake (8); //"true" one of these to reverse
pros::Motor intake2 (15, true);

//CONTROLLER
pros::Controller master (CONTROLLER_MASTER);

//SOLENOIDS
pros::ADIDigitalOut wings ('G', true);
pros::ADIDigitalOut descorer ('H', true);
pros::ADIDigitalOut hook ('D');
pros::ADIDigitalOut blocker('E', true);
	
//LIMIT SWITCH
pros::ADIDigitalIn kickerLimit ('B');
pros::ADIDigitalIn testLim ('F');

//IMU
pros::IMU imu (16); 

#endif