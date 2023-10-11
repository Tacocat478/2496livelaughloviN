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
    //prev_error = error; 
    error = target - input; 

    if(std::abs(error) < integralKI && std::abs(error) > 0.7){ //add max to prevent non-zero integral when error is extremely low (would cause overshoot)
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

    //derivative = error - prev_error; 
    

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
    LB.tare_position();
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
    imu.tare_heading();
    setConstants(1.39, 2.7, 0.0);
    float voltage;
    float position;
    int count = 0;
    float bound = 1.3;

    while(true){
        position = imu.get_heading();
        voltage = calc(target, position, 2, 20);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(-voltage, voltage);
        if ((target - position) <= bound && (target - position) >= -bound){
            //master.print(0, 0, "test");
            count++;
        }
        if (count >= 30) {
            break;
        }
        pros::delay(10);
    }
    chas_move(0,0);
}


#endif