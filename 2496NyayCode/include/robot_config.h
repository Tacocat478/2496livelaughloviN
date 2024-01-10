#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "main.h"
#include "pros/adi.hpp"
#include "pros/imu.hpp"

//CHASSIS
extern pros::Motor LF;
extern pros::Motor LB;
extern pros::Motor LM;
extern pros::Motor RF;
extern pros::Motor RB;
extern pros::Motor RM;

//KICKER
extern pros::Motor K;

//INTAKE
extern pros::Motor intake;

//CONTROLLER
extern pros::Controller master;

//SOLENOIDS
extern pros::ADIDigitalOut wings;
extern pros::ADIDigitalOut descorer;
extern pros::ADIDigitalOut hook;
extern pros::ADIDigitalOut blocker;

//LIMIT SWITCH
extern pros::ADIDigitalIn kickerLimit;

//IMU
extern pros::IMU imu;

#endif
