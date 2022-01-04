#include <Arduino.h>
#include "motor.h"
#include "log.h"

int counter = 0;
int currentwaitTime = 0;

void setMotor(int speed);

void initMotor(void){
  ledcSetup(motorpwmChannel, motorpwmFreq, motorpwmResolution);
  ledcAttachPin(motorPin, motorpwmChannel);

  setMotor(motorTurnSpeed);

  log_printf(MY_LOG_FORMAT("Motor PWM sucessfully initialized."));
}

void setMotor(int speed){
 ledcWrite(motorpwmChannel, speed);
 log_printf(MY_LOG_FORMAT("Motor pwm = %d"), speed);
}

void stopMotor()
{
  setMotor(0);
}

void setMotorByLevel(int level){
  currentwaitTime = motorPauseSpeeds[level];

  if (level == 0) stopMotor(); //Make sure that we also immediately stop the motor if we set it to 0;
}

void loopMotor()
{
  counter++;
  if (counter ==  100000)  {
    stopMotor();
  } else if (counter >=  currentwaitTime)  {
    if (currentwaitTime != -1) setMotor(motorTurnSpeed);
    counter = 0;
  }
}