# ifndef WHEEL_H
# define WHEEL_H
#include <Arduino.h>
#include <Servo.h>

using  uint = unsigned int;
//class class_name : access_specifier parent_name{ };
class Wheel: public Servo{ 
    private:
        int pwmPin;
        int position = 0; //initial position of the servo
    private:

    public:
        Wheel(int pwmPin);
        Wheel();
        //void move_fwd();
        //void move_backwd();
        
        
        
};
#endif