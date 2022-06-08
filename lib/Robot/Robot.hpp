#ifndef ROBOT_H
#define ROBOT_H
#include "Wheel.hpp"
#include "IMU.hpp"
#include "Adafruit_MPU6050.h"
#include <Servo.h>
class Robot{
    public:
    
    private:
  
    Wheel fL, fR; //front left and right wheels
    float angle;
    
    public:
        Robot();
        void turn30CW(); //turn 30 deg cw
        void turn30CCW(); //turn 30 deg ccw
        void moveFwd();
        void moveBackwd();
        float getAngle();
        float PID(float commanded, float measured, float dt,float kp,float ki, float kd);
        float _proportional(float commanded, float measured, float kp);
        float _integral(float commanded, float measured, float ki, float dt);
        float _derivative(float commanded, float measured, float kd, float dt);
    private:
        float _proportional(float commanded, float measured, float kp);
        float _integral(float commanded, float measured, float ki, float dt);
        float _derivative(float commanded, float measured, float kd, float dt);
        //float _integral(float commanded, float measured, float ki, float dt, float prevError);
        //float _derivative(float commanded, float measured, float kd, float dt, float prevError);
        float lastError = 0; //for the PID controller 

};

#endif 
