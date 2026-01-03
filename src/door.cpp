#include "config.h"
#include "door.h"
#include "alarm_state.h"
#include "alarm.h"
#include "blynk_extern.h"  

static bool lastDoorState = false;

void initDoorState() {
  lastDoorState = digitalRead(PIN_DOOR) == HIGH;
  alarm.doorOpen = lastDoorState;
}


void checkDoor() {
  int state = digitalRead(PIN_DOOR);
  bool doorOpen = (state == HIGH);

  // Cambiamento stato porta
  if (doorOpen != lastDoorState) {
    lastDoorState = doorOpen;
    alarm.doorOpen = doorOpen;
    Blynk.virtualWrite(V2, doorOpen);

    if (doorOpen) {
      Serial.println("🚪 Porta APERTA");
      alarm.alarmTriggered = false;
      Blynk.virtualWrite(VPIN_ALARM_TRIGGERED, 0);
    } else {
      Serial.println("🚪 Porta CHIUSA");
      alarm.alarmTriggered = false;
      alarm.manualSirenOff = false;
      alarm.cycles = 0;
      Blynk.virtualWrite(VPIN_ALARM_TRIGGERED, 0);

      Serial.println("✅ Evento resettato, pronto al retrigger");

    }
  }

  // Trigger sirena
  if (alarm.mode == ARMED &&
      doorOpen &&
      !alarm.sirenOn &&
      !alarm.alarmTriggered) {

    alarm.alarmTriggered = true; 
    sirenOn();
  }
}