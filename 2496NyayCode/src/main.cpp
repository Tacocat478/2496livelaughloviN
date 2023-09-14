#include "main.h"

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
	pros::lcd::set_text(1, "dillon is a bozo!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
void autonomous() {}

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
	//CHASSIS MOTORS
	pros::Motor LF (9); //"false" one side to reverse
	pros::Motor LB (10);
	pros::Motor RF (5, true);
	pros::Motor RB (1, true);

	//CATAPULT MOTORS
	pros::Motor CL (19);
	pros::Motor CR (20, true);
	bool cataDown = true;

	//INTAKE MOTORS
	pros::Motor intake (8); //"true" one of these to reverse

	//CONTROLLER
	pros::Controller master (CONTROLLER_MASTER);

	//WING SOLENOIDS
	pros::ADIDigitalOut wingL ('A');
	bool wings = false;
	wingL.set_value(LOW);

	//LIMIT SWITCH
	pros::ADIDigitalIn cataLimit ('B');


	//------------------------------------------------------------------------------------------------------------------


	while(true) {
		//CHASSIS
		int power = -(master.get_analog(ANALOG_LEFT_Y));
		int turn = -(master.get_analog(ANALOG_RIGHT_X));
		int left = power + turn;
		int right = power - turn;
		LF.move(left);
		LB.move(left);
		RF.move(right);
		RB.move(right);



		//INTAKE
		if (master.get_digital(DIGITAL_R1)){
			intake.move_velocity(200);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			intake.move_velocity(-200);
		}
		else{
			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.brake();
		}



		//WINGS
		if (master.get_digital_new_press(DIGITAL_L1)){
			wings = !wings;
			if (wings){
				wingL.set_value(HIGH);
			}
			else{
				wingL.set_value(LOW);
			}
		}



		//CATAPULT 
		CL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		CR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
			cataDown = false;
		}
		while(!cataDown){
			CL.move_velocity(100);
			CR.move_velocity(100);

			if (cataLimit.get_value() == true){
				cataDown = true;
				CL.brake();
				CR.brake();
			}
		}
		while(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			CL.move_velocity(100);
			CR.move_velocity(100);
		}
		CL.brake();
		CR.brake();



		pros::delay(2);
	}
}

