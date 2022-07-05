#include "Wheel.hpp"

Wheel::Wheel(int pwmPin){
    //Serial.println("Wheel");
    this->pwmPin = pwmPin;
    //this->servoObj.attach(pwmPin);
}

Wheel::Wheel(){}

void Wheel::move_fwd(){ 
    /*
    int newPosititon = this->position + 360; 
    this->servoObj.write(newPosititon);
    this->position = newPosititon;
    */
    this->servoObj.write(360);
}

void Wheel::move_backwd(){ 
    /*
    int newPosititon = this->position - 360; 
    this->servoObj.write(newPosititon);
    this->position = newPosititon;
    */
   this->servoObj.write(-360);
}


