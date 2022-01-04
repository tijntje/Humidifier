#include <Arduino.h>
#include "buttons.h"
#include "Button2.h"
#include "tft.h"
#include "fanPWM.h"
#include "log.h"
#include "humidity.h"
#include "motor.h"

#define DEFAULT_SETPOINT 60
#define DEFAULT_FANLEVEL 2
#define drawUI() drawUI(fanLevel, currentHumidity, humidityTooLow())
#define HYSTERISDEGREES 3

Button2 buttonUp = Button2(UPBUTTON);
Button2 buttonDown = Button2(DOWNBUTTON);

int fanLevel = DEFAULT_FANLEVEL;
int currentHumidity = 0;
int currentSetpoint = DEFAULT_SETPOINT;
int currentfanLevel = DEFAULT_FANLEVEL;

void buttonUpClicked(Button2& btn);
void buttonDownClicked(Button2& btn);
void buttonDownLongPressed(Button2& btn);
void buttonUpLongPressed(Button2& btn);
void buttonsLongPressedReleased(Button2& btn);
void updatedHumidity(float humidity);
bool humidityTooLow();
void humidityAlgorithm();

void initButtons()
{
  buttonUp.setClickHandler(buttonUpClicked);
  buttonUp.setLongClickDetectedHandler(buttonUpLongPressed);
  buttonUp.setLongClickDetectedRetriggerable(true);
  buttonUp.setLongClickHandler(buttonsLongPressedReleased);
  buttonUp.setDebounceTime(10);
  buttonUp.setDoubleClickTime(10);
  buttonUp.setLongClickTime(500);

  buttonDown.setClickHandler(buttonDownClicked);
  buttonDown.setLongClickDetectedHandler(buttonDownLongPressed);
  buttonDown.setLongClickDetectedRetriggerable(true);
  buttonDown.setLongClickHandler(buttonsLongPressedReleased);
  buttonDown.setDebounceTime(10);
  buttonDown.setDoubleClickTime(10);
  buttonDown.setLongClickTime(500);
}

void setup() {
  Serial.begin(115200);
  log_printf(MY_LOG_FORMAT("Setting things up ..."));

  initTFT();
  initPWMFan();
  initMotor();
  initHumidity(updatedHumidity);
  initButtons();

  log_printf(MY_LOG_FORMAT("Settings done. Have fun."));
}

void loop() {
  buttonUp.loop();
  buttonDown.loop();
  loopHumidity();
  loopMotor();
  humidityAlgorithm();
}

void buttonUpClicked(Button2& btn) {
  log_printf(MY_LOG_FORMAT("pressed up"));
  if (fanLevel < 3){
    fanLevel++;
    setPWMFanByLevel(fanLevel);
    setMotorByLevel(fanLevel);
    drawUI();
  }
}

void buttonDownClicked(Button2& btn) {
  log_printf(MY_LOG_FORMAT("pressed down"));
  if (fanLevel > 0){
    fanLevel--;
    setPWMFanByLevel(fanLevel);
    setMotorByLevel(fanLevel);
    drawUI();
  }
}

void buttonUpLongPressed(Button2& btn) {
  log_printf(MY_LOG_FORMAT("pressed up long"));
  if (currentSetpoint < 95){
    currentSetpoint += 5;
    drawSetpointChange(currentSetpoint);
  }
}

void buttonDownLongPressed(Button2& btn) {
  log_printf(MY_LOG_FORMAT("pressed down long"));
  if (currentSetpoint > 5){
    currentSetpoint -= 5;
    drawSetpointChange(currentSetpoint);
  }
}

void buttonsLongPressedReleased(Button2& btn) {
  drawUI();
}

void updatedHumidity(float humidity)
{
  log_printf(MY_LOG_FORMAT("Humidity: %d %%"), (int)humidity);
  currentHumidity = (int)humidity;
  drawUI();
}

void humidityAlgorithm()
{
 if (humidityTooLow() && fanLevel > 0 && currentfanLevel == 0) {
    currentfanLevel = fanLevel;
    setPWMFanByLevel(currentfanLevel);
    setMotorByLevel(currentfanLevel);
    log_printf(MY_LOG_FORMAT("activate fans, humidity too low."));
 } else if (currentfanLevel != 0 && !humidityTooLow()){
    currentfanLevel = 0;
    setPWMFanByLevel(currentfanLevel);
    setMotorByLevel(currentfanLevel);
    log_printf(MY_LOG_FORMAT("diable fans, setpoint reached."));
 }
}

bool humidityTooLow()
{
  if (currentHumidity < currentSetpoint) {
    return true;
  }  else {
    return false;
  }
}