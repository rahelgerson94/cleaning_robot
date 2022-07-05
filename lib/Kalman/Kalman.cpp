#include "Kalman.hpp"

Kalman::Kalman(){
    P[0][0] = 0;
    P[0][1] = 0;
    P[1][0] = 0;
    P[1][1] = 0;
    Q_angle = 0.01;
    Q_gyrobias = 0.003;
    R_measure = 0.011;
    angle = 0;
    bias = 0;
}

float Kalman::output(float newangle,float newrate, float dt){
    rate = newrate-bias;
    angle += dt*rate;
    P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_gyrobias * dt;
    y = newangle-angle;
    S = P[0][0] + R_measure;
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;
    angle += K[0] * y;
    bias += K[1] * y;

    P[0][0] -= K[0] * P[0][0];
    P[0][1] -= K[0] * P[0][1];
    P[1][0] -= K[1] * P[0][0];
    P[1][1] -= K[1] * P[0][1];
    return angle;
}

void Kalman::setAngle(float newangle){
    angle = newangle;
}

void Kalman::setParams(float Qa, float Qg, float Rm){
    Q_angle = Qa;
    Q_gyrobias = Qg;
    R_measure = Rm;
}