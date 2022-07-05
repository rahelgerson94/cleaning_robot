#pragma once

class Kalman{
  private:
    float Q_angle;
    float Q_gyrobias;
    float R_measure;
    float rate;
    float bias;
    float angle;
    float P[2][2];
    float S;
    float y;
    float K[2];
  public:
    Kalman();
    float output(float newangle,float newrate, float dt);
    void setAngle(float newangle);
    void setParams(float Qa, float Qg, float Rm);
};