/* #include <Arduino.h>
#include <Math.h>

#include "icm20948.hpp"
void printXYZ_setup(float x, float y, float z, int num_readings, char name[100] );
void printXYZ_loop(float x, float y, float z, char name );

IMU_9DoF imu;
float curr_time, dt;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  imu.init();
  Serial.println("done init");
  curr_time = 0;
  //imu.calibrate(); //calibrate_gyro(), calibrate_magn()
  //imu.get_heading_offset(); 
  
  Serial.println("yaw_raw");
}


void loop() {
  
  dt = micros() - curr_time;
  curr_time = micros();
  imu.update_all(dt/1000000.0);
  
  /* imu.read_imu(); //update gx, gy, gz, mx, my, mz, ax, ay, az
  imu.correct_magn();
  Serial.println(imu.yaw_raw() - imu.yaw_offset); */

  //float yaw_filt = imu.yaw;
  //float yaw_raw = atan2f(-imu.my,imu.mx)*(180/PI);
  //float yaw_raw = imu.get_magn_yaw();
  Serial.println( imu.yaw); 
  //Serial.print("\t");
  //Serial.println(yaw_raw); 

}

// this fct pretty prints x,y,z values from a sensor.
void printXYZ_setup(float x, float y, float z, int num_readings, char name[100] ){
  //name: sensor name, like gyro
   for (int i = 0; i < num_readings; i++){
    Serial.print(name); Serial.print(x); Serial.print(", ");
    Serial.print(name); Serial.print(y); Serial.print(", ");
    Serial.print(name); Serial.println(z);
  }
}

void printXYZ_loop(float x, float y, float z, char name ){
  //name: sensor name, like gyro
    Serial.print(name);  Serial.print(x);  Serial.print(" , ");
    Serial.print(name); Serial.print(y);  Serial.print(" , ");
    Serial.print(name);   Serial.print(z); Serial.print(" , ");
}

 */