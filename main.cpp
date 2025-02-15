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
	pros::lcd::set_text(1, "Hello PROS User!");

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

#define MOTOR_LEFT_FRONT 3
#define MOTOR_LEFT_BACK 2
#define MOTOR_LEFT_TOP 1

#define MOTOR_RIGHT_FRONT 5
#define MOTOR_RIGHT_BACK 4 
#define MOTOR_RIGHT_TOP 6

#define MOTOR_INTAKE 7
#define PNEUMATICS 1
void opcontrol() 
{
	pros::Controller master (CONTROLLER_MASTER); 
	pros::Motor left_front (MOTOR_LEFT_FRONT);
	pros::Motor left_back (MOTOR_LEFT_BACK);
	pros::Motor left_top (MOTOR_LEFT_TOP);

	pros::Motor right_front (MOTOR_RIGHT_FRONT);
	pros::Motor right_back (MOTOR_RIGHT_BACK);
	pros::Motor right_top (MOTOR_RIGHT_TOP);

	pros::Motor intake (MOTOR_INTAKE);
	pros::ADIAnalogOut wings (PNEUMATICS);

	while(true) 
	{
		left_front.move(master.get_analog(ANALOG_LEFT_Y)*-1);
		left_back.move(master.get_analog(ANALOG_LEFT_Y)*-1);
		left_top.move(master.get_analog(ANALOG_LEFT_Y));

		right_front.move(master.get_analog(ANALOG_RIGHT_Y));
		right_back.move(master.get_analog(ANALOG_RIGHT_Y));
		right_top.move(master.get_analog(ANALOG_RIGHT_Y)*-1);

		if(master.get_digital(DIGITAL_L1))
		{
			intake.move(100);
		}
		else if(master.get_digital(DIGITAL_L2))
		{
			intake.move(-100);
		}
		else
		{
			intake.move(0);
		}	


		if(master.get_digital(DIGITAL_R2))
		{
			wings.set_value(true);
		}
		else
		{
			wings.set_value(false);
		}

	}
}
