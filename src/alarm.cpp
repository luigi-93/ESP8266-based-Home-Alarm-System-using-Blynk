#include "config.h"
#include "alarm.h"
#include "alarm_state.h"
#include "blynk_extern.h" 


void sirenOn() {
  if (alarm.cycles >= MAX_CYCLES) {
    Serial.println("⚠ Limite cicli raggiunto. Sirena NON riparte.");
    return;
  }

  digitalWrite(PIN_RELAY, HIGH);
  alarm.sirenOn = true;
  alarm.manualSirenOff = false;
  alarm.sirenStartTime = millis();

  Blynk.virtualWrite(VPIN_SIREN_STATUS, 1);  // LED sirena ON
  Blynk.virtualWrite(VPIN_ALARM_TRIGGERED, 1);

  if (alarm.cycles == 0) {
    Blynk.logEvent("alarm_triggered", "Porta aperta → Sirena ON");
  } else {
    Blynk.logEvent("sirena_next_cycle", "La sirena riparte");
  }

  alarm.cycles++;

  Serial.print("🚨 Sirena ON - Ciclo ");
  Serial.print(alarm.cycles);
  Serial.print("/");
  Serial.println(MAX_CYCLES);
}

void sirenOffAuto() {
  digitalWrite(PIN_RELAY, LOW);
  alarm.sirenOn = false;

  // 🔁 Riarmo trigger SOLO se non ho superato i cicli
  if (alarm.cycles < MAX_CYCLES) {
    alarm.alarmTriggered = false;
  }

  Blynk.virtualWrite(VPIN_SIREN_STATUS, 0);
  Blynk.logEvent("auto_sirena_off", "Fine ciclo auto OFF (3 minuti)");

  Serial.println("⏱ Sirena OFF automatico");
}

void sirenOffManual() {
  digitalWrite(PIN_RELAY, LOW);
  alarm.sirenOn = false;
  alarm.manualSirenOff = true;
  alarm.cycles = 0;
  Blynk.virtualWrite(VPIN_SIREN_STATUS, 0);  
  Blynk.virtualWrite(VPIN_ALARM_TRIGGERED, 0);
  Blynk.logEvent("auto_sirena_off", "Sirena spenta manualmente");

  Serial.println("🛑 Sirena spenta MANUALMENTE - Cicli resettati");
}


void checkSirenTimer() {
  if (alarm.sirenOn && !alarm.manualSirenOff) {
    unsigned long elapsed = millis() - alarm.sirenStartTime;
    
    if (elapsed >= SIREN_DURATION) {
      sirenOffAuto();

      if (alarm.doorOpen && alarm.cycles < MAX_CYCLES) {
        Serial.println("⚠ Porta ancora aperta, sirena ripartirà tra poco...");
      }
    }
  }
}