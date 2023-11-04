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

void reset_encoders(){
    LF.tare_position();
    LB.tare_position();
    RF.tare_position();
    RB.tare_position();
}

void chas_move(int vLeft, int vRight){
    LF.move(vLeft);
	LB.move(vLeft);
	RF.move(vRight);
	RB.move(vRight);
}

void chas_moveFor(int distance, int velocity){
    reset_encoders();
    LF.move_absolute(distance, velocity);
    LB.move_absolute(distance, velocity);
    RF.move_absolute(distance, velocity);
    RB.move_absolute(distance, velocity);
}

void right_moveFor(int distance, int velocity){
    reset_encoders();
    RF.move_absolute(distance, velocity);
    RB.move_absolute(distance, velocity);
}

void left_moveFor(int distance, int velocity){
    reset_encoders();
    LF.move_absolute(distance, velocity);
    LB.move_absolute(distance, velocity);
}


void forwardMove(int target, float p){
    reset_encoders(); 
    setConstants(p, 0.0, 0.0);

    float voltage;
    float encoder_average;
    int count = 0;
    int bound = 100; //60

    while(true){
        
        encoder_average = (LF.get_position() + RF.get_position()) / 2;
        voltage = calc(target, encoder_average, 0, 0);
        master.print(0, 0, "%f", (target - encoder_average));

        chas_move(voltage, voltage); 
        if ((target - encoder_average) <= bound && (target - encoder_average) >= -bound) {
            count++; 
        }
        if (count >= 28) {
            break; 
        }                                   
        pros::delay(10);
    }
    chas_move(0,0); 
}

void forwardMove2(int target, float p){
    reset_encoders(); 
    setConstants(p, 0.0, 0.0);

    float voltage;
    float encoder_average;
    int count = 0;
    int bound = 800;

    while(true){
        
        encoder_average = (LF.get_position() + RF.get_position()) / 2;
        voltage = calc(target, encoder_average, 0, 0);
        master.print(0, 0, "%f", (target - encoder_average));

        chas_move(voltage, voltage); 
        if ((target - encoder_average) <= bound && (target - encoder_average) >= -bound) {
            count++; 
        }
        if (count >= 28) {
            break; 
        }                                   
        pros::delay(10);
    }
    chas_move(0,0); 
}

void turn(int target, float p, float i, float d, int KI, int maxI){
    imu.tare_rotation();
    //setConstants(1.39, 2.7, 0.0);
    setConstants(p, i, d);
    float voltage;
    float position;
    int count = 0;
    float bound = 1.5; //1.3

    while(true){
        position = imu.get_rotation();
        //voltage = calc(target, position, 2, 20);
        voltage = calc(target, position, KI, maxI);
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

void turn2(int target, float p, float i, float d, int KI, int maxI){
    imu.tare_rotation();
    //setConstants(1.39, 2.7, 0.0);
    setConstants(p, i, d);
    float voltage;
    float position;
    int count = 0;
    float bound = 7.5; //1.3

    while(true){
        position = imu.get_rotation();
        //voltage = calc(target, position, 2, 20);
        voltage = calc(target, position, KI, maxI);
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

void turn3(int target, float p, float i, float d, int KI, int maxI){
    imu.tare_rotation();
    //setConstants(1.39, 2.7, 0.0);
    setConstants(p, i, d);
    float voltage;
    float position;
    int count = 0;
    float bound = 2.0; //1.3  //2.0 

    while(true){
        position = imu.get_rotation();
        //voltage = calc(target, position, 2, 20);
        voltage = calc(target, position, KI, maxI);
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

void turn4(int target, float p, float i, float d, int KI, int maxI){
    imu.tare_rotation();
    //setConstants(1.39, 2.7, 0.0);
    setConstants(p, i, d);
    float voltage;
    float position;
    int count = 0;
    float bound = 4.0; //1.3  //2.0

    while(true){
        position = imu.get_rotation();
        //voltage = calc(target, position, 2, 20);
        voltage = calc(target, position, KI, maxI);
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