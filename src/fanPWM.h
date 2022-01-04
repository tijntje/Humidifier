#include <Arduino.h>

void initPWMFan(void);
void setPWMFanByLevel(int level);

const int pwmPin               = GPIO_NUM_17;
const int pwmFreq              = 25000;
const int pwmChannel           = 0;
const int pwmResolution        = 8;
const int fanSpeeds[] = {0,122,189,255};