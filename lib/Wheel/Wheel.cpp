#include "Wheel.hpp"

Wheel::Wheel(int pwmPin){
    //Serial.println("Wheel");
    this->pwmPin = pwmPin;
    //this->servoObj.attach(pwmPin);
}

Wheel::Wheel(){
    Serial.println("wheel created");
}

