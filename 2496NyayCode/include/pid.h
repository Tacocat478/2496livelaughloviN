#ifndef PID_H
#define PID_H

#include "main.h"
#include "robot_config.h"

void setConstants(float, float, float);
float calc(int, float, int, int);
void chas_moveFor(int, int);
void right_moveFor(int, int);
void left_moveFor(int, int);
void chas_move(int, int);
void reset_encoders();
void forwardMove(int, float);
void forwardMoveb(int, float);
void forwardMove2(int, float);
void forwardMove3(int, float);
void turn(int, float, float, float, int, int);
void turn2(int, float, float, float, int, int);
void turn3(int, float, float, float, int, int);
void turn4(int, float, float, float, int, int);


#endif