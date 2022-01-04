#include <Arduino.h>

void initMotor(void);
void setMotorByLevel(int level);
void loopMotor();

const int motorPin               = GPIO_NUM_21;
const int motorpwmFreq              = 50;
const int motorpwmChannel           = 4;
const int motorpwmResolution        = 16;
const int motorTurnSpeed            = 5000;
const int motorPauseSpeeds[]        = {-1,250000,250000,150000};
//const int motorPauseSpeeds[]        = {0,3500,4000,5000};