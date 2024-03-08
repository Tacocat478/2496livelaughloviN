#include "main.h"
#include "../include/robot_config.h"
#include "../include/driver.h"
#include "../include/pid.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "");


	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {


	
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
		//SKILS PROG (V2)
		/*
		K.move_velocity(600);
		int count = 0;
		while(count < 100){ //replace with near infinite number if only shooting during skils
			if (kickerLimit.get_new_press()) {
			count ++;
			pros::delay(300);
			}
		}
		K.brake();
		
		
		while (kickerLimit.get_value() == false){
		K.move_velocity(600);
		}
		K.brake();
		*/

		//AWP DESCORE (V2)
		/*
		intake.move_velocity(-200);
		chas_moveFor(300, 200);
		pros::delay(1000);
		chas_moveFor(1, 0);
		wings.set_value(HIGH);
		turnLeftFor(300, 40);
		pros::delay(1000);
		//turn2(-60, 1.50, 0.0, 0.0, 0, 0);
		wings.set_value(LOW);
		//turn2(-160, 1.35, 0.0, 0.0, 0, 0); //will need to revise kP
		turnRightFor(150, 40);
		pros::delay(1000);
		chas_moveFor(-900, 100);
		pros::delay(1500);
		turnLeftFor(100, 40);
		pros::delay(1000);
		chas_moveFor(-1350, 100);
		pros::delay(3000);
		*/
		//intake.move_velocity(-200);
		//forwardMoveb(-850, 0.15);
		//chas_moveFor(-200, 200);
		//pros::delay(1000);
		


		//SHOOT ONE (V2)
		/*
		K.move_velocity(600);
		int count2 = 0;
		while(count2 < 1){
			if (kickerLimit.get_new_press()) {
			count2 ++;
			pros::delay(300);
			}
		}
		K.brake();
		*/


		//FAR AWP PUSH (V2)
		/*
		intake.move_velocity(-200);
		turnLeftFor(260, 30);
		pros::delay(1000);
		chas_moveFor(1700, 70);
		pros::delay(2000);
		turnLeftFor(220, 40);
		pros::delay(1000);
		chas_moveFor(4000, 200);
		pros::delay(2000);
		chas_moveFor(-500, 200);
		intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		intake.brake();
		*/

		//CLOSE AWP PUSH (V1)
		/*
		turn3(45, 1.4, 0.0, 0.0, 0, 0);
		forwardMoveb(1100, 0.20); //1350
		//turn3(41, 1.75, 0.0, 0.0, 0, 0); //1.51
		turn3(45, 1.69, 0.0, 0.0, 0, 0);
		forwardMoveb(3000, 0.15);
		*/

		//OUTAKE
		//intake.move_velocity(-200);

		//5Ball (V2)
		/*
		imu.tare_rotation(); //initially resets the inertia sensor  reading
		intake.move_velocity(-200); //outtake to deploy intake
		pros::delay(200);
		intake.move_velocity(200);
		forwardMove(1100, 0.3, 0.0, 0.15, 105);
		turnCCW(35, 0); 
		wings.set_value(HIGH); //wings out
		forwardMove(600, 0.3, 0.0, 0.15, 78);
		turnCCW(110, 0); //turn to remove the triball
		wings.set_value(LOW); //wings in
		turnCCW(45, 0);
		forwardMove(800, 0.3, 0.0, 0.15, 78); 
		turnCCW(90, 0); //turn to face the goal
		intake.move_velocity(-200);
		forwardMove(2400, 1.0, 0.0, 0.15, 48);
		forwardMove(-600, 0.3, 0.0, 0.15, 30); 
		forwardMove(2400, 1.0, 0.0, 0.15, 48);
		forwardMove(-600, 0.3, 0.0, 0.15, 88);

		turnCCW(172, 0);
		intake.move_velocity(200);
		forwardMove(2400, 0.3, 0.0, 0.15, 145);

		turnCCW(30, 50); 
		intake.move_velocity(-400); //outtake
		forwardMove(700, 0.3, 0.0, 0.15, 78);
		pros::delay(600);

		turnCCW(140, 0); 
		intake.move_velocity(400); //intake
		forwardMove(1150, 0.3, 0.0, 0.15, 105); 

		turnCCWb(0); //0, 50   turnCCW(0, 40);
		wings.set_value(HIGH);
		intake.move_velocity(-200);
		forwardMove(1800, 0.3, 0.0, 0.15, 105); //125
		forwardMove(-1200, 0.3, 0.0, 0.15, 78);
		*/

		//TEST
		//imu.tare_rotation();
		//turnCW(90); //error goes above +-1 [always negative 1.6 ish] under 45 degrees, gets iffy above  95 degrees (is either perfect or around 1.5-2.0 --usually negative aroung 130 but above it's balanced positive to negative?) [usually negative error]; over 130 error is around -1.6 [110-120 is fine; 140 seems even?; 150 is negative low up to -1.6; 160-170 is fine; fixed slight error in 180 with conditional]
		//forwardMove(600, 0.3, 0.0, 0.15); //lowering d here = increasing d in turning

		//Far Rush (V2)
		/*
		imu.tare_rotation();
		intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		intake.move_velocity(-200);
		pros::delay(200);
		intake.move_velocity(200);
		forwardMove(2400, 0.3, 0.0, 0.15, 145);
		turnCW(90, 0);
		intake.move_velocity(-200);
		forwardMove(2400, 1.0, 0.0, 0.15, 75); //85
		forwardMove(-600, 0.3, 0.0, 0.15, 60); //68
		imu.tare_rotation();
		//turnCW(145, 0);
		turnCW(180, -10); //0
		intake.move_velocity(200);
		forwardMove(1200, 0.3, 0.0, 0.15, 90); //100
		forwardMove(-600, 0.3, 0.0, 0.15, 73);
		turnCWb(0, -10);
		intake.move_velocity(-200);
		forwardMove(2400, 1.0, 0.0, 0.15, 75);
		forwardMove(-600, 0.3, 0.0, 0.15, 70); //timeout could cause inaccurate lineup for next ball   78
		turnCW(140, -5);
		intake.move_velocity(200);
		forwardMove(1450, 0.3, 0.0, 0.15, 100); //115

		turnCW(56, -5); //50,0
		intake.brake();
		forwardMove(2250, 0.3, 0.0, 0.15, 125); //2300
		imu.tare_rotation();
		turnCCW(82, -5); //75,-5
		wings.set_value(HIGH);
		forwardMove(620, 0.3, 0.0, 0.15, 78); //500
		turnCCW(190, -5); //180,-10
		wings.set_value(LOW);
		intake.move_velocity(-200);
		turnCCW(117, 0); //110
		forwardMove(2400, 1.0, 0.0, 0.15, 85);
		forwardMove(-600, 0.3, 0.0, 0.15, 68);
		forwardMove(2400, 1.0, 0.0, 0.15, 85);
		forwardMove(-600, 0.3, 0.0, 0.15, 68);
		*/


		//progSkills
		imu.tare_rotation();
		turnCW(35, 0); //33
		forwardMove(4150, 0.3, 0, 0.15, 200);

		imu.tare_rotation();
		turnCCW(37, 0); //40
		forwardMove(1400, 0.3, 0.0, 0.15, 110);
		//turnCCW(90, 0);
		turnCCW(63, 0);
		forwardMove(200, 0.3, 0.0, 0.15, 78);
		turnCCW(90, 0);
		//wings.set_value(HIGH);
		intake.move_velocity(-200);
		forwardMove(4000, 6.0, 0.0, 0.15, 65); //85
		forwardMove(-600, 0.3, 0.0, 0.15, 68);
		forwardMove(4000, 6.0, 0.0, 0.15, 65);
		forwardMove(-300, 0.3, 0.0, 0.15, 68);
		//wings.set_value(LOW);
		intake.brake();

		imu.tare_rotation();
		turnCCWb(90, 0, 150);
		imu.tare_rotation();
		forwardMove(2300, 0.3, 0.0, 0.15, 145); //2350

		turnCWb(87, 0, 150); 
		forwardMove(1100, 0.3, 0.0, 0.15, 105); //600
		turnCWb(190, 0, 150); //180
		//forwardMove(4000, 1.0, 0, 0.15, 200);
		intake.move_velocity(-200);
		chas_move(-4000, -4000);
		pros::delay(3000);
		intake.brake();
		forwardMove(-1750, 0.3, 0.0, 0.15, 115); //1400  1750

		turnCWb(90, 0, 200);
		forwardMove(600, 0.3, 0, 0.15, 88); 
		turnCWb(190, 0, 200);
		wings.set_value(HIGH);
		intake.move_velocity(-200);
		//forwardMove(4000, 1.0, 0, 0.15, 200);
		chas_move(-4000, -4000);
		pros::delay(3000);
		wings.set_value(LOW);
		intake.brake();
		forwardMove(-1750, 0.3, 0.0, 0.15, 115);

		/*
		turnCWb(90, 0, 200);
		forwardMove(500, 0.3, 0, 0.15, 88); 
		turnCWb(190, 0, 200);
		wings.set_value(HIGH);
		///forwardMove(4000, 1.0, 0, 0.15, 100);
		chas_move(-4000, -4000);
		pros::delay(3000);
		wings.set_value(LOW);
		forwardMove(-1750, 0.3, 0.0, 0.15, 115);
		*/
		/*
		turnCWb(90, 0, 200);
		imu.tare_rotation();
		forwardMove(1200, 0.3, 0, 0.15, 105); 
		turnCWb(90, 0, 200);
		forwardMove(800, 0.3, 0, 0.15, 88); 
		turnCWb(160, 0, 200);
		wings.set_value(HIGH);
		*/
} 

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and 05tack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	imu.tare_rotation();
	//LF.tare_position();
	while(true){
		arcade_driverSixMotor();
		intake_driver();
		wings_driver();
		hook_driver();
		elevation_driver();
		kicker_driver();

		float positionTest = imu.get_rotation();
		//float target = 90.0;
		master.print(0, 0, "%f ", positionTest);

		
		//float encoder_averageNew = -(LM.get_position() + RM.get_position()) / 2;
		//master.print(0, 0, "%f ", encoder_averageNew);


		/*
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			autonomous();
		}
		*/

		pros::delay(100);//

	}

}

