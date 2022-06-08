#include "Robot.hpp"

Robot::Robot(){
    Serial.println("Robot");
    this->fR = Wheel(9);
    this->fL = Wheel(6);
    this->angle = 0;
}//end contsructor

void Robot::moveFwd(){
    fL.moveFwd();
    fR.moveBackwd();
}

void Robot::moveBackwd(){
    fL.moveBackwd();
    fR.moveFwd();
}

void Robot::turn30CW(){ //servo
    
}

float Robot::getAngle(){ //imu
    return 1.0;
}

float Robot::PID(float commanded, float measured, float dt,float kp,float ki, float kd){ //imu
    return 1.0;
}

float Robot::_proportional(float commanded, float measured, float kp){
    return kp*(commanded-measured); 
}
float Robot::_integral(float commanded, float measured, float Ki, float dt){
    this->PID_integral_part += (Ki*(commanded - measured)) / dt;
    return this->PID_integral_part;
}

float Robot::_derivative(float commanded, float measured, float Kd, float dt){
    return Kd*((commanded - measured) - this->PID_last_error ) *dt;
}