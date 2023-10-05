#ifndef PID_CPP
#define PID_CPP

#include "main.h"
#include "../include/pid.h"

float t_kp;
float t_ki;
float t_kd;
int error = 0;
int prev_error = 0;
int integral = 0;
int derivative = 0;
float power = 0;

void setConstants(float kp, float ki, float kd){ 
    t_kp = kp;
    t_ki = ki;
    t_kd = kd;
}

float calc (int target, float input, int integralKI, int maxI){
    prev_error = error; 
    error = target - input; 

    if(std::abs(error) < integralKI){ //add max to prevent non-zero integral when error is extremely low (would cause overshoot)
        integral += error;            
    }
    else{
        integral = 0;
    }
    
    if(integral >= 0){
        integral = std::min(integral, maxI); 
    }
    else{
        integral = std::max(integral, -maxI);
    }

    derivative = error - prev_error; 

    power = t_kp*error + t_ki*integral + t_kd*derivative; 

    return power; 
}

void chas_move(int vLeft, int vRight){
    LF.move(vLeft);
	LB.move(vLeft);
	RF.move(vRight);
	RB.move(vRight);
}

void reset_encoders(){
    LF.tare_position();
    LB.get_target_position();
    RF.tare_position();
    RB.tare_position();
}

void forwardMove(int target){
    setConstants(0.39, 0.15, 0.01);

    float voltage;
    float encoder_average;
    int count = 0;

    reset_encoders(); 
    while(true){
        
        encoder_average = (LF.get_position() + RF.get_position()) / 2;
        voltage = calc(target, encoder_average, 200, 20);


        chas_move(voltage, voltage); 
        if (abs(target - encoder_average) <= 3) count++; 
        if (count >= 28) break; 
                                                       
        pros::delay(10);
    }
    chas_move(0,0); 
}

void turn(int target){
    setConstants(1, 0.0, 0.0);

    float voltage;
    float position;
    int count = 0;

    while(true){
        master.print(0, 0, "", (target - position));
        position = imu.get_rotation();
        voltage = calc(target, position, 0, 20);

        chas_move(voltage, -voltage);
        if (abs(target - position) <= 1.5) count++;
        if (count >= 28) break;
        pros::delay(10);
    }
    chas_move(0,0);
}


#endif