#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\main.h"

#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\adi.h"
#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\adi.hpp"
#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\llemu.hpp"
#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\misc.h"
#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\motors.h"
#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\rtos.hpp"
#include <cmath>
#include <queue>
#include <vector>


using namespace pros;
using namespace std;

typedef pair<double, double> pdd;


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
{
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

int autonCase = 2;

void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Nuh Uh!");

	pros::lcd::register_btn1_cb(on_center_button);
	//climberR.set_brake_mode(MOTOR_BRAKE_HOLD);
	//climberL.set_brake_mode(MOTOR_BRAKE_HOLD);
	gyro.reset();

	pros::delay(500);
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

void competition_initialize() {
	while(true) {
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			autonCase--;
			if(autonCase < 1){
				autonCase = 2;
			}
		}
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			autonCase++;
			if(autonCase > 2){
				autonCase = 1;
			}
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			break;
		}
		controller.print(0, 0, "autonCase: %d", autonCase);
	}
}

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
/*
void rotate_on_spot(double power){
    driveLeftBackB.move(power);
    driveLeftFront.move(power);
    driveRightBackB.move(power);
    driveRightFront.move(power);
}

void drive_straight(double power){
	driveLeftBackB.move(power);
    driveLeftFront.move(power);
    driveRightBackB.move(-power);
    driveRightFront.move(-power);
}

void rotate_to_angle(double angle){
    double current = 0; // power to wheels
    double integralActiveZone = 5;// tune (angle in degrees)

    double angleErrorTotal = 0;
    double lastAngleError = 0;
    double proportion = 0;
    double integral = 0;
    double derivative = 0;

    // tune again but better
    double kp = 5;
    double ki = 1.05;
    double kd = 20;

    gyro.set_heading(0); // Turning clockwise = number increases
	double currentAngle = 0;
    double targetAngle = currentAngle + angle; // check sign on angle
	if (targetAngle > 360) {
		targetAngle -= 360;
	}
	if (targetAngle < -360) {
		targetAngle += 360;
	}

	int timer = 0;
	int timeOut = 10;

	if(targetAngle > 0) { // positive angle
		while(currentAngle > targetAngle + 0.5 || currentAngle < targetAngle - 0.5){
			currentAngle = gyro.get_heading(); // get current angle from gyro
			double angleError = targetAngle - currentAngle; 

			// Prevents integrals from adding on large amounts of numbers and causing the motors to spin too fast.
			if(angleError < integralActiveZone && angleError > -integralActiveZone && angleError != 0) {
				angleErrorTotal += angleError;  
			} else {
				angleErrorTotal = 0;
			}

			// Cap for integral
			if(angleErrorTotal > 300/ki){
				angleErrorTotal = 300/ki;
			}

			// Imediately sets deravitive to 0 instead of having it gradully return to 0.
			if(angleError == 0){
				derivative = 0;
			}

			proportion = angleError * kp;
			integral = angleErrorTotal * ki;    
			derivative = (angleError - lastAngleError) * kd;

			lastAngleError = angleError;

			current = proportion + integral + derivative;

			rotate_on_spot(current);

			if(angleError < 0.5 && angleError > -0.5) {
				timer++;

				if(timer >= timeOut){
					rotate_on_spot(0);
					break;
				}
			} else  {
				timer = 0;
			}

			pros::delay(20);
		}
		rotate_on_spot(0);
	} else if (targetAngle < 0) { // negative angle
		targetAngle += 360;
		while(currentAngle > targetAngle + 0.5 || currentAngle < targetAngle - 0.5){
			currentAngle = gyro.get_heading(); // get current angle from gyro
			if(currentAngle > 0 && currentAngle < 5) {
				currentAngle = 359;
			}
			double angleError = targetAngle - currentAngle;

			// Prevents integrals from adding on large amounts of numbers and causing the motors to spin too fast.
			if(angleError < integralActiveZone && angleError > -integralActiveZone && angleError != 0) {
				angleErrorTotal += angleError;  
			} else {
				angleErrorTotal = 0;
			}

			// Cap for integral
			if(angleErrorTotal > 300/ki){
				angleErrorTotal = 300/ki;
			}

			// Imediately sets deravitive to 0 instead of having it gradully return to 0.
			if(angleError == 0){
				derivative = 0;
			}

			proportion = angleError * kp;
			integral = angleErrorTotal * ki;    
			derivative = (angleError - lastAngleError) * kd;

			lastAngleError = angleError;

			current = proportion + integral + derivative;

			rotate_on_spot(current);

			if(angleError < 0.5 && angleError > -0.5) {
				timer++;
				if(timer >= timeOut){
					rotate_on_spot(0);
					break;
				}
			} else  {
				timer = 0;
			}

			pros::delay(20);
		}
	}
}

double meters_to_motor(double meter){
	double motor_encoder_unit = meter / (3.25 * 0.0254 * 3.14159265358979323846) * 300 * 3 / 2; // 3/2 is gearing raito, motor spins 3 times wheels only spin 2 times
	return motor_encoder_unit;
}

void drive_to_point(pdd targetCoord, bool reverse)
{
    // Queue stores the target points that we hope to hit in the path
    // All points are relative so 5, 5 would mean 5 units forwards 5 units to the right.
    // front of bot
    //  ^ 
    //  |  +
    //  |----->

    double current = 0;
    double integralActiveZone = 30;

    double kp = 0.11; // small cuz motor encoder units are very big
    double ki = 0.01;
    double kd = 0.3;

    double displacementTotal;
    double lastDisplacement;
    double proportion;
    double integral;
    double derivative;

	double currentX = 0;
	double currentY = 0;
	driveLeftFront.tare_position(); // sets current position to 0 
	driveRightFront.tare_position();

	double targetX = currentX + meters_to_motor(targetCoord.first);
	double targetY = currentY + meters_to_motor(targetCoord.second);

	currentX = driveLeftFront.get_position();
	currentY = driveRightFront.get_position();

	double displacementX = targetX - currentX; 
	double displacementY = targetY - currentY;
	double displacement = sqrt(displacementX*displacementX + displacementX*displacementY);
	displacement = reverse ? -displacement : displacement;
	double targetDisplacement = displacement;
	
	// calculate rotation change if any
	double theta = atan(displacementY / displacementX) * 180 / 3.14159265358979323846;
	double a = reverse ? -displacementX : displacementX;
	double b = reverse ? -displacementY : displacementY;

	if(a == 0 && b < 0){ 
		theta = -90.0;
	}
	else if(a == 0 && b > 0){
		theta = 90.0;
	}
	else if (a < 0 && b == 0) {
		theta = 180.0;
	}
	else if (a < 0) {
		theta += 180.0;
	}
	if(theta > 180) {
		theta = -360 + theta;
	}

	//copy pid and modify for rotation
	rotate_to_angle(theta);

	currentX = driveLeftFront.get_position();
	currentY = driveRightFront.get_position();

	int timer = 0;
	int timeOut = 10;
	int timer2 = 0;
	int hardStop = 100;

	while(true){
		displacement = targetDisplacement - driveLeftFront.get_position();

		// Prevents integrals from adding on large amounts of numbers and causing the motors to spin too fast.
		if(displacement < integralActiveZone && displacement != 0) {
			displacementTotal += displacement;
		} else {
			displacementTotal = 0;
		}

		// Cap for integral
		if(displacementTotal > 100/ki){
			displacementTotal = 100/ki;
		}

		// Imediately sets deravitive to 0 instead of having it gradully return to 0.
		if(displacement == 0){
			derivative = 0;
		}

		proportion = displacement * kp;
		integral = displacementTotal * ki;    
		derivative = (displacement - lastDisplacement) * kd;

		lastDisplacement = displacement;

		current = proportion + integral + derivative;

		drive_straight(current);

		if(displacement < 150 && displacement > -150) {
			timer++;
			if(timer >= timeOut){
				drive_straight(0);
				break;
			}
		} else {
			timer = 0;
		}
		if(timer2 >= hardStop) {
			break;
		}
		pros::delay(20);
		timer2++;

		pros::lcd::set_text(2, to_string(timer));
		pros::lcd::set_text(3, to_string(timer2));
		pros::lcd::set_text(4, to_string(displacement));
    }
}

void autonomous()
{
	queue<pdd> target_coords;

	if(autonCase == 1){ // defensive side, descore, push aliance triball in, touch bar.
		climberR = 127;
		climberL = 127;
		pros::delay(400);
		climberR = 0;
		climberL = 0;

		Intake = 127;
		target_coords.push({1.5, 0});
		
		while(!target_coords.empty()) {
			drive_to_point(target_coords.front(), false);
			target_coords.pop();
		}

		Intake = 0;
		
		rotate_to_angle(-90);
		drive_straight(127);
		pros::delay(500);
		drive_straight(0);
		pros::delay(600);
		drive_to_point({-0.07, 0}, true);
		rotate_to_angle(-90);
		drive_to_point({1.45, 0}, false);
		rotate_to_angle(-90);
		climberR = 0;
		drive_to_point({0.75, 0}, false);
	}
	else if(autonCase == 2){ // offensive side, score first triball, pick up triball2, drop triball 2, pick up triball 3, open walls, push all in
		climberR = 127;
		climberL = 127;
		pros::delay(600);
		// climberR = -127;
		// climberL = -127;
		// pros::delay(300);
		climberR = 0;
		climberL = 0;

		Intake = 127;
		target_coords.push({1.45, 0});
		
		while(!target_coords.empty()) {
			drive_to_point(target_coords.front(), false);
			target_coords.pop();
		}

		Intake = 0;
		
		rotate_to_angle(90);
		drive_straight(127);
		pros::delay(500);
		drive_straight(0);
		pros::delay(600);
		drive_to_point({-0.10, 0}, true);

		rotate_to_angle(180);
		Intake = 127;
		drive_to_point({0.40, 0}, false);
		pros::delay(750);
		rotate_to_angle(180);
		Intake = 0;
		drive_to_point({0.75, 0}, false);
		drive_to_point({-0.10, 0}, true);


		rotate_to_angle(180);
		Intake = 127;
		drive_to_point({0.62, 0}, false);
		pros::delay(754);
		rotate_to_angle(180);
		Intake = 0;
		drive_to_point({0.85, 0}, false);
		drive_to_point({-0.10, 0}, true);


		climberL = 127;
		climberR = 127;
		pros::delay(1000);
		climberL = 0;
		climberR = 0;

		// rotate_to_angle(147);
		// drive_to_point({0.73, 0}, false);
		// Intake = 127;
		// pros::delay(800);
		// rotate_to_angle(180);
		// Intake = 0;
		// walling.set_value(true);
		// drive_to_point({0.7, 0}, false);

	} else if (autonCase == 3) { // skills, push both triballs in, back up to matchload bar, shoot triballs into net, drive under bar and push triballs from the side in, move to front of net and push in.
		Fly1 = -120;
		Fly2 = -120;
	}
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

int intake = 0;
bool intaketoggle = false;
bool shoottoggle = false;
bool expanded = false;
bool expanded2 = false;
bool expanded3 = false;
bool windown = true;
float counter = 0;
bool inNormal = false;
bool flyReverse = false;
bool intakeallowed = false;
int power = 125;

pros::ADIAnalogIn sensor('C');
pros::ADIDigitalOut blocker ('G');
pros::ADIDigitalOut descore ('F');

void opcontrol()
{
	int timer = 0;
	int walls = 0;
	int block = 0;
	int flyR = 0;
	int fly = 0;
	int pwr = 0;
	int ds = 0;

	while (true)
	{
		setDriveMotors();

		// Turns intake on

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			climberR = 127;
			climberL = 127;
		}
		else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{

			climberR = -127;
			climberL = -127;
		}
		else
		{
			climberR = 0;
			climberL = 0;
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			Intake = 127;
		}
		else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			Intake = -127;
		} 
		else {
			Intake = 0;
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) && walls <= timer)
		{
			expanded = !expanded;
			walling.set_value(expanded);
			walls = timer + 10;
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) && block <= timer)
		{
			expanded2 = !expanded2;
			blocker.set_value(expanded2);
			block = timer + 10;
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) && ds <= timer)
		{
			expanded3 = !expanded3;
			descore.set_value(expanded3);
			ds = timer + 10;
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && flyR <= timer){
			flyReverse = !flyReverse;
			flyR = timer + 10;
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && shoottoggle == false && fly <= timer)
		{
			power = flyReverse ? -power : power;
			Fly1 = -power;
			Fly2 = -power;

			shoottoggle = true;
			fly = timer + 15;
		}
		else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && shoottoggle == true && fly <= timer)
		{

			Fly1 = 0;
			Fly2 = 0;

			shoottoggle = false;
			fly = timer + 15;
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && pwr <= timer)
		{
			if (power < 126)
			{
				power = (int)power + 2;
			}
			pwr = timer + 5;
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && pwr <= timer)
		{
			if (power > 2)
			{
				power = (int)power - 2;
			}
			pwr = timer + 5;
		}

		controller.print(0, 0, "Counter: %d", power);
		// Reverses Intake

		// Winding the Winch backwards

		// Shooting the winch
		
		timer++;
		pros::delay(20);
	}
}