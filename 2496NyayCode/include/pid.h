#ifndef PID_H
#define PID_H

#include "main.h"
#include "robot_config.h"

void setConstants(float, float, float);
float calc(int, float, int, int);
void chas_move(int, int);
void reset_encoders();
void forwardMove(int);
void turn(int);

#endif