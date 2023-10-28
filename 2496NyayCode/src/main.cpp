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
		//SKILS PROG
		/*
		KL.move_velocity(85);
		KR.move_velocity(85);
		int count = 0;
		while(count < 45){
			if (kickerLimit.get_new_press()) {
			count ++;
			pros::delay(300);
			}
		}
		KL.brake();
		KR.brake();
		*/

		/*
		while (kickerLimit.get_value() == false){
		KL.move_velocity(120);
		KR.move_velocity(120);
		}
		
		pros::delay(500);		
		forwardMove(200, 0.20);
		turn3(50, 1.65, 0.0, 0.0, 0, 0); //1.75  1.61  1.55
		forwardMove(1150, 0.15); //1250  950
		turn3(-14, 3.5, 0.0, 0.0, 0, 0);
		forwardMove(3300, 0.11); //3800

		turn2(-90, 1.27, 0.0, 0.0, 0, 0);
		forwardMove(1200, 0.15);

		turn2(-90, 1.27, 0.0, 0.0, 0, 0);
		forwardMove(1150, 0.15); //1250
		turn2(90, 1.27, 0.0, 0.0, 0, 0);
		forwardMove(1800, 0.15); //1600
		turn2(90, 1.27, 0.0, 0.0, 0, 0);
		wings.set_value(LOW); //wings out
		forwardMove2(2000, 0.15);
		forwardMove(-1500, 0.15);
		turn3(17, 6.0, 0.0, 0.0, 0, 0); 
		forwardMove2(2000, 0.15);
		forwardMove(-1500, 0.15);
		wings.set_value(HIGH);
		
 
		turn3(55, 1.60, 0.0, 0.0, 0, 0);
		forwardMove2(2800, 0.15); //3500
		turn2(-120, 1.16, 0.0, 0.0, 0, 0);
		forwardMove2(1500, 0.20);
		forwardMove2(-1500, 0.20);
		*/
		
		
		//AWP DESCORE
		descorer.set_value(LOW);
		pros::delay(500);
		turn2(-50, 1.65, 0.0, 0.0, 0, 0);
		descorer.set_value(HIGH);
		turn2(55, 1.60, 0.0, 0.0, 0, 0);
		forwardMove(300, 0.20);
		turn3(-17, 6.0, 0.0, 0.0, 0, 0); 
		intake.move_velocity(200);
		intake2.move_velocity(200);
		forwardMove(1000, 0.15);
		blocker.set_value(LOW);


		


		

		//SHOOT ONE
		/*
		KL.move_velocity(85);
		KR.move_velocity(85);
		int count2 = 0;
		while(count2 < 1){
			if (kickerLimit.get_new_press()) {
			count2 ++;
			pros::delay(300);
			}
		}
		KL.brake();
		KR.brake();
		*/


		//FAR AWP PUSH
		/*
		turn3(-45, 1.69, 0.0, 0.0, 0, 0);
		forwardMove(1350, 0.20);
		turn3(-41, 1.51, 0.0, 0.0, 0, 0);
		forwardMove(3000, 0.15);
		*/
		


		//CLOSE AWP PUSH
		/*
		turn3(45, 1.69, 0.0, 0.0, 0, 0);
		forwardMove(1350, 0.20);
		turn3(41, 1.51, 0.0, 0.0, 0, 0);
		forwardMove(3000, 0.15);
		*/



		
		
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
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
	//imu.tare_rotation();
	//LF.tare_position();
	while(true){
		arcade_driver();
		intake_driver();
		wings_driver();
		hook_driver();
		descorer_driver();
		kicker_driver();
		blocker_driver();

		//float positionTest = imu.get_rotation();
		//float target = 90.0;
		//master.print(0, 0, "%f %f", positionTest, (target - positionTest));
		//master.print(0,0,"%f",imu.get_rotation());
		//master.print(0,0,"%f",LF.get_position());

		/*
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			autonomous();
		}
		*/

		pros::delay(100);//

	}

}

