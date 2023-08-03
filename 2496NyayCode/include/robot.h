#ifndef ROBOT_H
#define ROBOT_H

#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"

//chassis
extern pros::Motor RF;
extern pros::Motor RB;

extern pros::Motor LF;
extern pros::Motor LB;

//intake
extern pros::Motor intakeL;
extern pros::Motor intakeR;

//controller
extern pros::Controller con;
#endif