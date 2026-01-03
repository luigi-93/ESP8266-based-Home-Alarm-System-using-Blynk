#include "blynk_extern.h"       
#include "config.h"
#include "alarm_state.h"
#include "alarm.h"

BLYNK_WRITE(V0)  // arm/disarm allarme
{
  int v = param.asInt();
  alarm.mode = v ? ARMED : DISARMED;

  if (v) {
    alarm.cycles = 0;
    alarm.manualSirenOff = false;
    Blynk.logEvent("alarm_on", "Allarme armato");
    Serial.println("🔒 Allarme ARMATO");
  } else {
    if (alarm.sirenOn) {
      sirenOffManual();
    }
    alarm.cycles = 0;
    alarm.manualSirenOff = false;
    Blynk.logEvent("alarm_off", "Allarme disarmato");
    Serial.println("🔓 Allarme DISARMATO");
  }
}

BLYNK_WRITE(V1)  // STOP SIRENA (push)
{
  if (param.asInt() == 1 && alarm.sirenOn) {
    sirenOffManual();
    Serial.println("🛑 STOP sirena da app");
  }
}

BLYNK_CONNECTED() {
  Serial.println("📡 Connesso a Blynk");
  
  // Sincronizza stato iniziale
  Blynk.virtualWrite(V0, alarm.mode);
  Blynk.virtualWrite(V2, alarm.doorOpen);
  Blynk.virtualWrite(VPIN_SIREN_STATUS, alarm.sirenOn);
  Blynk.virtualWrite(VPIN_ALARM_TRIGGERED, alarm.alarmTriggered);
  
}
