#ifndef __GLOBAL__
#define __GLOBAL__

#include "main.h"


namespace glb
{
    // ports ===============================
    #define P_RF 13
    #define P_RB 11
    #define P_LF 9
    #define P_LB 8

    #define P_INTAKEL 14
    #define P_INTAKER 15


    // objects =============================
    pros::Controller con(pros::E_CONTROLLER_MASTER);
    pros::Motor intakeL(P_INTAKEL, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor intakeR(P_INTAKER, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor RF(P_RF, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor RB(P_RB, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor LF(P_LF, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor LB(P_LB, pros::E_MOTOR_GEARSET_06, true);

}

#endif