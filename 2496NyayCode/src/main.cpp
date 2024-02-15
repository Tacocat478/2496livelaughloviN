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
		forwardMove(1100, 0.20); //1350
		//turn3(41, 1.75, 0.0, 0.0, 0, 0); //1.51
		turn3(45, 1.69, 0.0, 0.0, 0, 0);
		forwardMove(3000, 0.15);
		*/

		//OUTAKE
		//intake.move_velocity(-200);

		//TEST
		imu.tare_rotation();
		//setConstants(1.16, 0.0, 0.0);
		setConstants(1.8, 0, 1.5); //2   6
		turnNew(90);
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

		//float positionTest = imu.get_rotation();
		//float target = 90.0;
		//master.print(0, 0, "%f ", positionTest);
		//master.print(0,0,"%f",imu.get_rotation());
		//master.print(0,0,"%f",LF.get_position());

		/*
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			autonomous();
		}
		*/

		imu.tare_rotation();
		//setConstants(1.16, 0.0, 0.0);
		setConstants(3, 0, 2.5); //2   6
		if (master.get_digital_new_press(DIGITAL_LEFT)){
			turnNew(90);
		}


		pros::delay(100);//

	}

}

