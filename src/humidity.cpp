#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "humidity.h"
#include "log.h"

DHT_Unified dht(DHTPIN, DHTTYPE);

typedef void (*callback_function)(float);
callback_function humidityReceived;

int latest_humidity = 0;

void initHumidity(callback_function pFunc) {
  dht.begin();

  humidityReceived = pFunc;

  log_printf(MY_LOG_FORMAT("Done setting up humidity sensor..."));
}

void loopHumidity() {
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    if (latest_humidity != (int)event.relative_humidity){
      latest_humidity = (int)event.relative_humidity;
      humidityReceived(latest_humidity);
    }
  }
}