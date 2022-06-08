# ifndef WHEEL_H
# define WHEEL_H
#include <Arduino.h>
#include <Servo.h>

using  uint = unsigned int;
class Wheel{
    private:
        int pwmPin;
        
        int position = 0; //initial position of the servo
    public:
        Servo servoObj;
    private:
    public:
        Wheel(int pwmPin);
        Wheel();
        void moveFwd();
        void moveBackwd();
        
        
        
};
#endif