#include "ota.h"
#include <ArduinoOTA.h>


void setupOTA() {
  ArduinoOTA.setHostname("wemos-alarm");
  ArduinoOTA.begin();
}

