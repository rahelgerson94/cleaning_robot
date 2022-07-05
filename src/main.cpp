// Basic demo for accelerometer readings from Adafruit MPU6050
#include "Robot.hpp"
#include "icm20948.hpp"

#include <Wire.h>
#include <Servo.h>
Robot R = Robot();
Wheel Left(6); 
Wheel Right(9);

void setup(){
  Serial.begin(115200);
  Left.servoObj.attach(6);
  Right.servoObj.attach(9);

}

void loop(){
  //R.moveFwd();
  Left.servoObj.write(0); //left is a touch faster 
  Right.servoObj.write(130);
  
  //Serial.println("moved fwd");
}


/*this fct is stupid, but i don't wanna delete it. yet. */
double KFilt(double U){
  //constants (static)
  static const double R = 40; //noise covariance (it's actually 10)
  static const double H = 1.00; //measurement map scalar
  static double Q = 10; //initial estimated covariance
  static double P = 0; //initial error covariance (must be 0)
  static double U_hat =0; //initial estimated state (assume we don't know)
  static double K = 0; //initial Kalman gain
  //begin
  K = P*H/(H*P*H+R); //update kalman gain
  U_hat = U_hat + K*(U-H*U_hat); // update estimated
  //update error covariance
  P= (1-K*H)*P+Q;
  //now let's return the estimate of U_hat (the state)
  return U_hat;
}


float testPID(float commanded, float measured_range[2], const float dt, const float kp, const float ki, const float kd, int num_ite, Robot robo){
  /* 
  purpose: find the min, max values that robot::pid() outputs
  so that we can map those values to actual sensor values.
  
  non-obvious inputs: 
  -commanded:
  -measured_range: the range of readings from the sensor  w/o  correction
  for example, due to motor imperfections the trajecttory is an arc shape.
  imu goes from 0 to ~90
  so imu max, min would be (0, 1.4) not the absolute (max, min) of -1.4, 1.4
  this corresponds to turning the imu from -90 to 90. 
*/
  
   
  float u_max = -10000000000;
  float u_min = 10000000000;
  float u; //output of pid: P+I+D
  float dt = .000003; //seconds
  for (int i = 0; i < num_ite; i ++){
    u = robo.pid(commanded, measured, dt, kp, ki, kd);
    //if (u_max < ){

    }
  }

}//end testPID