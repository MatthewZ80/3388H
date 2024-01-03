#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\main.h"
#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\motors.h"
// 1 AND 14 ARE BAD

// Drive Motors :: Slide Side is the Front
pros::Motor driveLeftBackB(10, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBackT(9, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront(6, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor driveRightBackT(12, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBackB(19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(16, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

// Intake Motors

pros::Motor climberR(20, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor climberL(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

// Winch Motors
pros::Motor Fly1(20, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor Fly2(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor Intake(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

// Expansion
pros::ADIDigitalOut walling('H');
// pros::ADIDigitalOut blocker('G');

// controller=
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Gyro
pros::Imu gyro(17);