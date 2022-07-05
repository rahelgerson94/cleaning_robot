#ifndef ROBOT_H
#define ROBOT_H
#include "Wheel.hpp"
#include "icm20948.hpp"
#include <Servo.h>
class Robot{
    public:
    
    private:
  
    Wheel fL, fR; //front left and right wheels
    float angle;
    IMU_9DoF imu;
    
    public:
        Robot();
        void turn30ccw(); //turn 30 deg cw
        void turn30cw(); //turn 30 deg ccw
        void move_fwd();
        void move_backwd();
        float getAngle();
        float pid(float commanded, float measured, float dt, float kp, float ki, float kd);
        
    private:
        float proportional(float commanded, float measured, float kp);
        float integral(float commanded, float measured, float ki, float dt);
        float derivative(float commanded, float measured, float kd, float dt);
        //float _integral(float commanded, float measured, float ki, float dt, float prevError);
        //float _derivative(float commanded, float measured, float kd, float dt, float prevError);
        float pid_integral_part; //a running sum from i=0 to i=t
        float pid_last_error; //used to compute d/dt (e(t))

};

#endif 
