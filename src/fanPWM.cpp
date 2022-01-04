#include <Arduino.h>
#include "fanPWM.h"
#include "log.h"

void initPWMFan(void){
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(pwmPin, pwmChannel);

  setPWMFanByLevel(0);

  log_printf(MY_LOG_FORMAT("Fan PWM sucessfully initialized."));
}

void setPWMFan(int speed){
 ledcWrite(pwmChannel, speed);
 log_printf(MY_LOG_FORMAT("fan pwm = %d"), speed);
}

void setPWMFanByLevel(int level){
  setPWMFan(fanSpeeds[level]);
}