#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include "blynk_extern.h"    
#include <ArduinoOTA.h>

#include "config.h"
#include "alarm_state.h"
#include "alarm.h"
#include "door.h"
#include "ota.h"


AlarmState alarm;
BlynkTimer timer;


void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Serial.println("\n\n=================================");
  Serial.println("🚨 SISTEMA ALLARME v2.0");
  Serial.println("=================================\n");


  Serial.println();
  Serial.print("Tentativo connessione WiFi a SSID: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long start = millis();
  const unsigned long timeout = 20000; 

  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > timeout) {
      Serial.println("Errore: connessione WiFi fallita (timeout)");
      break;
    }
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("Connesso a WiFi, IP: ");
    Serial.println(WiFi.localIP());
    
    Blynk.config(BLYNK_AUTH_TOKEN);
    Blynk.connect();
  } else {
    Serial.println("WiFi non connessa");
  }
  
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_DOOR, INPUT_PULLUP);

  digitalWrite(PIN_RELAY, LOW);

  initDoorState();

  if (alarm.mode == ARMED && alarm.doorOpen) {
    Serial.println("⚠ Riavvio con porta APERTA → Sirena immediata");
    sirenOn();
  }

  timer.setInterval(1000, checkDoor);
  timer.setInterval(500, checkSirenTimer);

  setupOTA();

  Serial.println("\n✅ Sistema allarme avviato");
  Serial.println("=================================\n");
}

void loop() {
  Blynk.run();
  timer.run();
  ArduinoOTA.handle();
}
