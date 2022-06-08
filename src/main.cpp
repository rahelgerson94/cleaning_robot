// Basic demo for accelerometer readings from Adafruit MPU6050
#include "Robot.hpp"
#include <Wire.h>
#include <Servo.h>
//Robot R = Robot();
Wheel Left(6); 
Wheel Right(9);

void setup(){
  Serial.begin(9600);
  Left.servoObj.attach(6);
  Right.servoObj.attach(9);
}

void loop(){
  //R.moveFwd();
  Left.servoObj.write(0); //left is a touch faster 
  Right.servoObj.write(130);
  //Serial.println("moved fwd");
}


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