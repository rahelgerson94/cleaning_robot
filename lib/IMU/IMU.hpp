
#ifndef IMU_H
#define IMU_H
#include "Sensor.hpp"
class IMU: public Sensor{
    public:
    IMU();
    void calibrate();
    void init();
};
#endif
