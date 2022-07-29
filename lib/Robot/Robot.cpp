#include "Robot.hpp"

Robot::Robot(){
    Serial.println("Robot");
    this->fR = Wheel(9);
    this->fL = Wheel(6);
    this->angle = 0;
}//end contsructor

/* void Robot::move_fwd(){
    fL.move_fwd(); //write 0 to left
    fR.move_backwd(); //write 130 to right
}

void Robot::move_backwd(){
    fL.move_backwd();
    fR.move_fwd();
} */

void Robot::turn30cw(){ //servo
    
}

float Robot::getAngle(){ //imu
    return 1.0;
}

/* this function outputs a control signal, which is sent to an acturator 
commanded, kp, ki, kd: user inputs
measured: the sensor measuremnts
dt: comes from void loop; the time between calls to PID()  
*/
float Robot::pid(float commanded, float measured, float dt, float kp, float ki, float kd){ //imu
    return this->proportional(commanded, measured, kp) + this->integral(commanded, measured, ki, dt) + this->derivative(commanded, measured, kd, dt); 
}

float Robot::proportional(float commanded, float measured, float kp){
    return kp*(commanded-measured); 
}
float Robot::integral(float commanded, float measured, float Ki, float dt){
    this->pid_integral_part += (Ki*(commanded - measured)) / dt;
    return this->pid_integral_part;
}

float Robot::derivative(float commanded, float measured, float Kd, float dt){
    float delta_error = (commanded - measured) - this->pid_last_error;
    float error_part =  Kd* (delta_error*dt);
    this->pid_last_error = commanded - measured;
    return error_part;
}