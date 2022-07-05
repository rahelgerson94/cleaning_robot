#include "Kalman.hpp"
#include "ICM_20948.h"
class IMU_9DoF: public ICM_20948_I2C{
    public:
    IMU_9DoF();
    void init();
    void calibrate(); // used in setup
    void update_all(float dt); //updates all the properties
    void read_imu();
    

    private:
    void get_heading_offset(); 
    void correct_magn(); //apply x-formations from calibrate_magn() to mx, my, mz 
    void apply_yaw_offset();
    void apply_gyro_offsets();
    void apply_offsets(); //needs to be called whenever updating sensor vals
    void updateRPY(float dt); //updates R,P,Y
    void update_yaw(float dt); //kalman yaw
    float yaw_raw(); //atan(my,mx)
    void calibrate_gyro( );
    void calibrate_magn( );
    void dot33by13(float A[3][3], float x[3], float out[3]);


    public:
    float yaw=0, yaw_offset=0;
    float pitch=0;
    float roll=0;
    float ax, ay, az;
    float gx, gy, gz;
    float gx_offset = 0, gy_offset = 0, gz_offset = 0;
    float mx, my, mz;
    float declination = 12.0; //set according to your region.
    //m1, a1, and b were found using a seperate python script, adapted from https://teslabs.com/articles/magnetometer-calibration/
    float M1[3][3]; 
    float A1[3][3]; //the stretch, rotation and shift matrix that we multiply mx,my,mz by. 
    float b[3] = {0} ;
    float F = 46.4844; //uT; F is the magnetic field strength in your area and the radius of the sphere you want your mag. measurements to be. 

    
    private:
    float last_time = 0;
    Kalman kalman_yaw;
    Kalman kalman_pitch; //need to implemenet
    Kalman kalman_roll; //need to implemenet
    
};