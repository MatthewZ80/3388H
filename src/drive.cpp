#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\main.h"
#include "C:\Users\Matthew\Desktop\Not-Scuffed-main\include\pros\rtos.hpp"

void setDrive(int left, int right){

    driveLeftBackT = left;
    driveLeftBackB = left;
    driveLeftFront = left;
    driveRightBackT = right;
    driveRightBackB = right;
    driveRightFront = right;
}


void translate(int units, int voltage)
{

    setDrive(voltage,-voltage);
      
    pros::delay(units);
    setDrive(0,0);
        
    
}


// float looparound(int degrees)
// {
//   float pi = 3.141592653589793238462643383279502884;
//   return 180/pi*(atan2f(sinf(degrees*pi/180), cosf(degrees*pi/180)));
// }
// void rotate(int degree, int direction){


//     /*
//     rotat.set_heading(0);
//     pros::delay(1200);
//     float cur = 0;
//     if(direction ==-1){
//         cur += degrees;
//         while(rotat.get_rotation() < cur ){
//             setDrive(70,70); 
//         }
//     }
//     else{
//         cur = 360;
//         cur -= degrees; 
//             while(rotat.get_rotation() > cur ){
//             setDrive(-70,-70); 
//         }
//     }

// */
//  // default postive turning goes right, since right is always right. 

//     setDrive(0,0);
//   float kI = 60;
//   rotat.set_heading(0);
//   float degrees = fabs(looparound(degree));

//     //mess with these two values to adjust turning
//   float kP = 500;
//   float kD = 500;

//   float avggyro = fabs(looparound(rotat.get_heading()));

//   float errors = degrees - avggyro;
//   float preverror = errors;

//   int cnt = 0;
//   int maxcnt = 0;
//   //first turn

//   while (cnt < 8 && maxcnt < 300)
//   {
//     avggyro = fabs(looparound(rotat.get_heading()));

//     errors = degrees - avggyro;
//     //errors = looparound(errors);

//     std::cout<<"bruh<" << errors << std::endl;
//     // - kD*(errors-preverror)     - kD*(errors-preverror)
//     setDrive(-(kP*(errors)- kD*(errors-preverror))*direction, (kP*(errors)- kD*(errors-preverror))*-direction);
//     //setDrive(-direction, -direction);
//     if (errors < 2 && errors > -2)
//     {
//       cnt+=1;
//     }
//     else{
//       cnt = 0;
//     }
//     preverror = errors;
//     maxcnt++;
//     pros::delay(10);
//   }
// }


void setDriveMotors(){ 

   // int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
   // int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = -1 *  controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int power = 1*controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    power = power;   
  
    int Left = power - (turn*1);
    int Right = power + (turn*1);
    if(abs(Left) <2){
        Left =0;
    }   
    if(abs(Right) < 2){
        Right =0;
    }   

    //(newjoyy-prevjoyy) = change in joy y
    //max threshold = tunable value
    //if change > max, motors = + prwvvy max_threshold -> joy y max threshold

    setDrive((Left),(Right));

    // value devided 1.5, for accelration, once spooled up, using motor encoders once 50% speed, go down tp 1.2 div, then 80, 1.1, then 1.0  
}