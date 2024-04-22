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
int iniDiff;
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

    derivative = error - prev_error; 
    
    extraD = 0;
    if (abs(iniDiff) >= 80 && abs(iniDiff) <= 100) extraD = 2.0;
    if (abs(iniDiff) >= 130 && abs(iniDiff) <= 155) extraD = -0.3;
    if (abs(iniDiff) > 155 && abs(iniDiff) <= 175) extraD = 0.7;
    if (abs(iniDiff) > 175) extraD = -1;

    float ap = -6.9479*pow(10,-10), bp = 3.7943*pow(10, -7), cp = -0.0000784358, dp = 0.00761929, fp = -0.352518, gp = 7.75784;
    float ad = -2.1188*pow(10,-9), bd = 9.8641*pow(10,-7), cd = -0.000157061, dd = 0.00901409, fd = -0.0463471, gd = -0.560709;

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
    time += 0;//20  5
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


void forwardMove(int target, float p, float i, float d, int timeLimit){
    //target = -target; //1200 is one tile
    reset_encoders(); 
    setConstants(p, i, d);

    float voltage;
    float encoder_average;
    float count = 0;

    while(true){
        
        encoder_average = -(LM.get_position() + RM.get_position()) / 2;
        voltage = fwdCalc(target, encoder_average, 0, 0);
        master.print(0, 0, "%f %f", (target - encoder_average), encoder_average);

        chas_move(-voltage, -voltage); 

        
        if (count >= timeLimit) { 
            break; 
        }   
        count++;
        
        
        pros::delay(10);
        

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
        voltage = fwdCalc(target, encoder_average, 0, 0);
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

void turnCW(int target, int extraTime){
    //imu.tare_rotation();
    float voltage;
    float position;
    float count = 0;
    float bound = 1.5; 
    float boundTwo = 0;
    //float timeLimit = calcTime(target);
    float timeLimit = calcTime(abs(target-imu.get_rotation())); //changed 3/4 after 5 ball
    iniDiff = target-imu.get_rotation();

    while(true){
        position = imu.get_rotation();
        voltage = calc(target, position, KI, maxI);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(-voltage, voltage);

        /*
        if (count > timeLimit + extraTime) {
            break;
        }
        */

        count++;
        pros::delay(10);
        /*if (abs(position-target) > 1.5) count++;
        master.print(0, 0, "%f", count); */
    }
    chas_move(0,0);
}

void turnCCW(int target, int extraTime){
    //imu.tare_rotation();
    float voltage;
    float position;
    int count = 0;
    float bound = 1.5; 
    float boundTwo = 0;
    //float timeLimit = calcTime(target);
    float timeLimit = calcTime(abs(target+imu.get_rotation())); //changed 3/4 after 5 ball

    while(true){
        position = -imu.get_rotation();
        voltage = calc(target, position, KI, maxI);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(voltage, -voltage);

        if (count > timeLimit + extraTime) {
            break;
        }

        count++;
        pros::delay(10);
    }
    chas_move(0,0);
}

void turnCCWb(int target, int extraBound, int timeOut){
    //imu.tare_rotation();
    float voltage;
    float position;
    int count = 0;
    int count2 = 0;
    float bound = 1.5; 
    float boundTwo = 0;
    //float timeLimit = calcTime(target);

    while(true){
        //CW
        position = -imu.get_rotation();
        voltage = calc(target, position, KI, maxI);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(voltage, -voltage);

        
        if (count > 30 + extraBound || count2 > timeOut) {
            break;
        }
        

        if(abs(target - position) < 5) count++; //5
        count2++;
        pros::delay(10);
    }
    chas_move(0,0);
}

void turnCWb(int target, int extraBound, int timeOut){
    //imu.tare_rotation();
    float voltage;
    float position;
    int count = 0;
    int count2 = 0;
    float bound = 1.5; 
    float boundTwo = 0;

    while(true){
        //CW
        position = imu.get_rotation();
        voltage = calc(target, position, KI, maxI);
        master.print(0, 0, "%f %f", (target - position), voltage);

        chas_move(-voltage, voltage);

        
        if (count > 20 + extraBound || count2 > timeOut) { //30
            break;
        }
        

        if(abs(target - position) < 5) count++;
        count2++;
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

void driveArcL(double theta, double radius, int timeout){
    //setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    setConstants(0.25, 0, 0.01);
    double ltarget = 0;
    double rtarget = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    //imu.tare_heading();
    int count = 0;
    int time = 0;
    reset_encoders();
    master.clear();
    //int timeout = 5000;
    ltarget = double((theta / 360) * 2 * pi * radius); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius + 222));
    while (true){

        setConstants(0.25, 0, 0);

        double heading = imu.get_heading() - init_heading;
        if (theta > 0){
            if (heading > 30){
                heading = heading - 360;
            }
        } else {
            if (heading > 300){
                heading = heading - 360;
            }    
        }
        double encoderAvgL = LF.get_position();
        //encoderAvgL = 100;
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;
        int voltageL = calc(ltarget, encoderAvgL, 0, 0);

        if(voltageL > 70){
            voltageL = 70;
        } else if (voltageL < -70){
            voltageL = -70;
        }
        int voltageR = calc(rtarget, encoderAvgR, 0, 0);

        if(voltageR > 100){
            voltageR = 100;
        } else if (voltageR < -100){
            voltageR = -100;
        }

        //delay(50);
        //con.print(1, 0, "Aut 0: %f        ", float(encoderAvgL));
        double leftcorrect = (encoderAvgL * 360) / (2 * pi * radius);
        int fix = int(heading + leftcorrect);
        fix = fix * 10;
        master.print(0, 0, "Aut 0: %f        ", float(voltageR + fix));
        
        fix = 0;
        chas_move( (voltageL - fix), (voltageR + fix));
        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (count >= 20 || time > timeout){
            break;
        } 
        time += 10;
        pros::delay(10);

    }
}

void driveArcR(double theta, double radius, int timeout){
    //setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    setConstants(0.25, 0, 0.01);
    double ltarget = 0;
    double rtarget = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    if (init_heading > 180){
        init_heading = init_heading - 360;
    }
    //imu.tare_heading();
    int count = 0;
    int time = 0;
    reset_encoders();
    master.clear();
    //int timeout = 5000;
    ltarget = double((theta / 360) * 2 * pi * (radius + 222)); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius));
    while (true){

    
        setConstants(0.25, 0, 0.01);


        double heading = imu.get_heading() - init_heading;
        if (theta > 0){
            if (heading > 300){
                heading = heading - 360;
            }
        } else {
            if (heading > 30){
                heading = heading - 360;
            }    
        }
        double encoderAvgL = LF.get_position();
        //encoderAvgL = 100;
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;
        int voltageL = calc(ltarget, encoderAvgL, 0, 0);

        if(voltageL > 100){
            voltageL = 100;
        } else if (voltageL < -100){
            voltageL = -100;
        }
        int voltageR = calc(rtarget, encoderAvgR, 0, 0);

        if(voltageR > 70){
            voltageR = 70;
        } else if (voltageR < -70){
            voltageR = -70;
        }

        //delay(50);
        //con.print(1, 0, "Aut 0: %f        ", float(encoderAvgL));
        double rightcorrect = (encoderAvgR * 360) / (2 * pi * radius);
        int fix = int(heading - rightcorrect);
        fix = fix * 10;
        master.print(0, 0, "Aut 0: %f        ", float(heading));
        

        chas_move( (voltageL - fix), (voltageR + fix));
        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (count >= 20 || time > timeout){
            break;
        } 
        time += 10;
        pros::delay(10);
    }
}

#endif