#ifndef DRIVER_H
#define DRIVER_H

#include "main.h"
#include "robot_config.h"

void arcade_driverSixMotor();
void intake_driver();
void intakeMove_velocity(int);
void intakeBrake();
void wings_driver();
void hook_driver();
void elevation_driver();
void kicker_driver();
void blocker_driver();

#endif