#ifndef PID_CPP
#define PID_CPP

#include "main.h"
#include "../include/pid.h"

float t_kp;
float t_ki;
float t_kd;
float extraD = 0;
float KI = 0;
float maxI = 200;
int error = 0;
int prev_error = 0;
int integral = 0;
int derivative = 0;
float power = 0;
bool negative;


void setConstants(float kp, float ki, float kd){ 
    t_kp = kp;
    t_ki = ki;
    t_kd = kd;
}

float calc (int target, float input, int integralKI, int maxI){
    prev_error = error; 
    error = target - input; 

    if(std::abs(error) < 6){ //add max to prevent non-zero integral when error is extremely low (would cause overshoot)
        integral += error;            
    }

    
    // if(integral >= 0){
    //     integral = std::min(integral, maxI); 
    // }
    // else{
    //     integral = std::max(integral, -maxI);
    // }

    derivative = error - prev_error; 

    extraD = 0;
    if (abs(target) > 35 && abs(target) < 45) extraD = 3;
    if (abs(target) < 35) extraD = 6;
    if (abs(target) > 85 && abs(target) < 105) extraD = 0; //-0.5
    if (abs(target) == 180) extraD = 0; //-1


    float ap = -4.0326*pow(10,-10), bp = 2.3486*pow(10, -7), cp = -0.0000528563, dp = 0.00570746, fp = -0.297477, gp = 7.91727;
    float ad = -2.4118*pow(10,-9), bd = 0.00000130151, cd = -0.000262289, dd = 0.0238383, fd = -0.917237, gd = 18.6136;
    t_kp = ap*pow(target, 5) + bp*pow(target, 4) + cp*pow(target, 3) + dp*pow(target, 2) + fp*target + gp;
    t_kd = ad*pow(target, 5) + bd*pow(target, 4) + cd*pow(target, 3) + dd*pow(target, 2) + fd*target + gd + extraD;
    t_ki = 0.0;
    
    power = t_kp*error + t_ki*integral + t_kd*derivative; 

    return power; 
}

float fwdCalc (int target, float input, int integralKI, int maxI){
    prev_error = error; 
    error = target - input; 

    if(std::abs(error) < 6){ //add max to prevent non-zero integral when error is extremely low (would cause overshoot)
        integral += error;            
    }

    
    // if(integral >= 0){
    //     integral = std::min(integral, maxI); 
    // }
    // else{
    //     integral = std::max(integral, -maxI);
    // }

    derivative = error - prev_error; 
    
    power = t_kp*error + t_ki*integral + t_kd*derivative; 

    return power; 
}

float calcTime(int target){
    float at = -2.7626*pow(10,-9), bt = 0.0000011704, ct = -0.00015766, dt = 0.00555204, ft = 0.518313, gt = 17.5455;
    float time = at*pow(target, 5) + bt*pow(target, 4) + ct*pow(target, 3) + dt*pow(target, 2) + ft*target + gt;
    time += 20;
    return time;
}

void reset_encoders(){
    LF.tare_position();
    LM.tare_position();
    LB.tare_position();
    RF.tare_position();
    RM.tare_position();
    RB.tare_position();
}

void chas_move(int vLeft, int vRight){
    LF.move(vLeft);
    LM.move(vLeft);
	LB.move(vLeft);
	RF.move(vRight);
    RM.move(vRight);
	RB.move(vRight);
}

void chas_moveFor(int distance, int velocity){
    reset_encoders();
    LF.move_absolute(distance, velocity);
    LM.move_absolute(distance, velocity);
    LB.move_absolute(distance, velocity);
    RF.move_absolute(distance, velocity);
    RM.move_absolute(distance, velocity);
    RB.move_absolute(distance, velocity);
}

void turnLeftFor(int distance, int velocity){
    reset_encoders();
    LF.move_absolute(distance, velocity);
    LM.move_absolute(distance, velocity);
    LB.move_absolute(distance, velocity);
    RF.move_absolute(-distance, velocity);
    RM.move_absolute(-distance, velocity);
    RB.move_absolute(-distance, velocity);
}

void turnRightFor(int distance, int velocity){
    reset_encoders();
    LF.move_absolute(-distance, velocity);
    LM.move_absolute(-distance, velocity);
    LB.move_absolute(-distance, velocity);
    RF.move_absolute(distance, velocity);
    RM.move_absolute(distance, velocity);
    RB.move_absolute(distance, velocity);
}

void right_moveFor(int distance, int velocity){
    reset_encoders();
    RF.move_absolute(distance, velocity);
    RM.move_absolute(distance, velocity);
    RB.move_absolute(distance, velocity);
}

void left_moveFor(int distance, int velocity){
    reset_encoders();
    LF.move_absolute(distance, velocity);
    LM.move_absolute(distance, velocity);
    LB.move_absolute(distance, velocity);
}


void forwardMove(int target, float p){
    //target = -target; //1200 is one tile
    reset_encoders(); 
    setConstants(p, 0.0, 0.0);

    float voltage;
    float encoder_average;
    int count = 0;
    int bound = 100; //60

    while(true){
        
        encoder_average = -(LM.get_position() + RM.get_position()) / 2;
        voltage = fwdCalc(target, encoder_average, 0, 0);
        master.print(0, 0, "%f %f", (target - encoder_average), encoder_average);

        chas_move(-voltage, -voltage); 

        /*
        if (abs(target - encoder_average) <= bound) {
            count++; 
        }
        if (count >= 10) { //28
            break; 
        }                                   
        pros::delay(10);
        */
    }
    chas_move(0,0); 
}

void forwardMoveb(int target, float p){
    reset_encoders(); 
    //setConstants(p, 0.0, 0.0);

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
   // setConstants(p, 0.0, 0.0);

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
        if (count >= 10) { //28
            break; 
        }                                   
        pros::delay(10);
    }
    chas_move(0,0); 
}

void forwardMove3(int target, float p){
    reset_encoders(); 
    //setConstants(p, 0.0, 0.0);

    float voltage;
    float encoder_average;
    int count = 0;
    int bound = 500;

    while(true){
        
        encoder_average = (LF.get_position() + RF.get_position()) / 2;
        voltage = calc(target, encoder_average, 0, 0);
        master.print(0, 0, "%f", (target - encoder_average));

        chas_move(voltage, voltage); 
        if ((target - encoder_average) <= bound && (target - encoder_average) >= -bound) {
            count++; 
        }
        if (count >= 10) {
            break; 
        }                                   
        pros::delay(10);
    }
    chas_move(0,0); 
}

void forwardMove4(int target, float p){
    reset_encoders(); 
    //setConstants(p, 0.0, 0.0);

    float voltage;
    float encoder_average;
    int count = 0;
    int bound = 1000;

    while(true){
        
        encoder_average = (LF.get_position() + RF.get_position()) / 2;
        voltage = calc(target, encoder_average, 0, 0);
        master.print(0, 0, "%f", (target - encoder_average));

        chas_move(voltage, voltage); 
        if ((target - encoder_average) <= bound && (target - encoder_average) >= -bound) {
            count++; 
        }
        if (count >= 10) {
            break; 
        }                                   
        pros::delay(10);
    }
    chas_move(0,0); 
}

void turnCW(int target){
    //imu.tare_rotation();
    float voltage;
    float position;
    float count = 0;
    float bound = 1.5; 
    float boundTwo = 0;
    float timeLimit = calcTime(target);

    while(true){
        //CW
        position = imu.get_rotation();
        voltage = calc(target, position, KI, maxI);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(-voltage, voltage);

        if (count > timeLimit) {
            break;
        }

        count++;
        pros::delay(10);
        /*if (abs(position-target) > 1.5) count++;
        master.print(0, 0, "%f", count); */
    }
    chas_move(0,0);
}

void turnCCW(int target){
    //imu.tare_rotation();
    float voltage;
    float position;
    int count = 0;
    float bound = 1.5; 
    float boundTwo = 0;
    float timeLimit = calcTime(target);

    while(true){
        //CW
        position = -imu.get_rotation();
        voltage = calc(target, position, KI, maxI);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(voltage, -voltage);

        if (count > timeLimit) {
            break;
        }
    
        pros::delay(10);
    }
    chas_move(0,0);
}

void turn(int target, float p, float i, float d, int KI, int maxI){
    imu.tare_rotation();
    setConstants(p, i, d);
    float voltage;
    float position;
    int count = 0;
    float bound = 1.5; //1.3

    while(true){
        position = imu.get_rotation();
        voltage = calc(target, position, KI, maxI);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(-voltage, voltage);
        if ((target - position) <= bound && (target - position) >= -bound){
            count++;
        }
        if (count >= 10) { //30
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
        if (count >= 10) { //30
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
    float bound = 3.5; //2.0 

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
        if (count >= 10) { //30
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
        if (count >= 10) { //30
            break;
        }
        pros::delay(10);
    }
    chas_move(0,0);
}

void turn5(int target, float p, float i, float d, int KI, int maxI){
    imu.tare_rotation();
    //setConstants(1.39, 2.7, 0.0);
    setConstants(p, i, d);
    float voltage;
    float position;
    int count = 0;
    float bound = 9.0; //1.3  //2.0

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
        if (count >= 10) { //30
            break;
        }
        pros::delay(10);
    }
    chas_move(0,0);
}



#endif