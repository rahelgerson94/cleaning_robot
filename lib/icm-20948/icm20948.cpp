#include "icm20948.hpp"


/*The value of the last bit of the I2C address.
On the SparkFun 9DoF IMU breakout the default is 1, and when 
the ADR jumper is closed the value becomes 0 */              
#define AD0_VAL 1  
#define err_thresh 2 //deg
#define num_ite 10 //increase to imporve yaw_offset accuracy 

IMU_9DoF::IMU_9DoF(){ //IMU_9DoF extends ICM_20948
}

void IMU_9DoF::init(){
    //Wire.begin();
    //Wire.setClock(400000);
    this->begin(Wire, AD0_VAL );
    if (!this->status != ICM_20948_Stat_Ok){
        Serial.println("Trying again...");
        delay(500);
    }
}

/* ensures that our starting orientation given by the magnetometer, atan(mx/my) 
is zero. This is *after* magn. has been calibrated  */
void IMU_9DoF::get_heading_offset(){
        for (int ite = 0; ite < num_ite; ite++){
            /*get ave yaw readings */
            float yaw_old = 0;
            for (int i = 0; i < 1000; i++){
                this->read_imu(); //update gx, gy, gz, mx, my, mz, ax, ay, az
                this->correct_magn();
                yaw_old += (this->yaw_raw() - this->yaw_offset);
            }
            yaw_old /= 1000;
            this->yaw_offset += yaw_old;
            if (abs(yaw_old) <= err_thresh){
                break;
            }
            else{
               // Serial.println("rerunning");
            }
         }
}


/*update sensor readings, takes into account
scale factors */
void IMU_9DoF::read_imu(){
    this->getAGMT();
    this->mx = this->magX( ); // micro teslas
    this->my = this->magY( ); // micro teslas
    this->mz = this->magZ( ); // micro teslas

    this->ax = this->accX( ); // milli g's
    this->ay = this->accY( ); // milli g's
    this->az = this->accZ( ); // milli g's

    this->gx = this->gyrX( ); // degrees per second
    this->gy = this->gyrY( ); // degrees per second
    this->gz = this->gyrZ( ); // degrees per second
}


void IMU_9DoF::update_all(float dt){
    this->read_imu(); //update gx, gy, gz, mx, my, mz, ax, ay, az
    this->correct_magn();
    this->updateRPY(dt); 
    this->apply_offsets();
}
void IMU_9DoF::apply_offsets(){
    this->apply_gyro_offsets();
    this->yaw -= this->yaw_offset;
   
}

void IMU_9DoF::apply_gyro_offsets(){
   //the below offsets are known by calling this->calibrate()
    this->gx -= this->gx_offset;
    this->gy -= this->gy_offset;
    this->gz -= this->gz_offset; 
}

void IMU_9DoF::updateRPY(float dt){
    this->update_yaw(dt);
    //TODO: do this for roll, pitch
    //this->update_roll(); 
    //this->update_pitch();
}

/*kalman yaw*/
void IMU_9DoF::update_yaw(float dt){
    float magn_angle = this->yaw_raw();
    //float magn_angle = atan2f(mx,my)*(180/PI);
    this->yaw = this->kalman_yaw.output(magn_angle, this->gz, dt);
    
}

/*raw yaw*/
float IMU_9DoF::yaw_raw(){ 
/* helper fct to calc yaw using mx, my readings
see AN203_Compass_Heading_Using_Magnetometers by Honeywell */
    return atan2f(-this->my, this->mx)*(180/PI);
}

void IMU_9DoF::calibrate(){
    this->calibrate_gyro();
    //this->calibrate_yaw();
    this->calibrate_magn();
} 

void IMU_9DoF::calibrate_gyro(){
    for (int i = 0; i < 1000; i++){
        this->read_imu();
            this->gx_offset += this->gx;
            this->gy_offset += this->gy;
            this->gz_offset += this->gz;
    }
    this->gx_offset /= 1000;
    this->gy_offset /= 1000;
    this->gz_offset /= 1000;
    
    /* Serial.println("calibration of gyro complete");
    Serial.print("gx = "); Serial.print(gx); Serial.print(", ");
    Serial.print("gy = "); Serial.print(gy); Serial.print(", ");
    Serial.print("gz = "); Serial.println(gz); */
    
}

void IMU_9DoF::calibrate_magn(){
    //M1, A, and b values are hardcoded and were found using a seperate python script 
    //the goal is for the arduino to perform that calibration algorithm each time upon boot up, 
    //but for now they will do
    //Serial.println("[calibrate_magn]");
    float M1_temp[3][3] = {
        {1.66359101,  0.02128539, -0.05283598},
        { 0.02128539,  1.70818964,  0.0592756 },
        {-0.05283598,  0.0592756 ,  1.84949856}};
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            this->M1[i][j] = M1_temp[i][j];
    }

    //float b_temp[3] = { 40.41825072, -34.45484142, 35.2237839};
    float b_temp[3] = { 40.51841328, -29.88374101,  35.59953287};
    for (int i = 0; i < 3; i++)
        this->b[i] = b_temp[i];
    
    float A1_temp[3][3] = {
    {1.08181,	-0.0377921,	0.00930331},
    {-0.0377921, 1.01835, 0.000453415},
    {0.00930331, 0.000453415, 1.08691}};


    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            this->A1[i][j] = A1_temp[i][j];
    }
}

/*apply the Ax+b to each reading x 
this is greyed out because A is essentially 
a diagonal of ones, meaning the mag. requires neglible
stretch, rotation, and shift */
void IMU_9DoF::correct_magn(){
    this->mx-= b[0];
    this->my-=b[1];
    this->mz -= b[2];
                      
    /* float m[3] = {this->mx,this->my, this->mz}; //uncalibrated
    float m_c[3] ={0,0,0}; //calibrated
    float temp = 0;
    //perform dot(A, samples-b)
    for (int i = 0; i < 3; i++){ 
        for (int j = 0; j < 3; j++)
            temp += A1[i][j]*(m[j] - b[j]);
        m_c[i] =  temp;
        temp = 0;
    }
    //update 
    this->mx = m_c[0];
    this->my = m_c[1];
    this->my = m_c[2]; */
}