#ifndef CONFIG_H
#define CONFIG_H

// --- WIFI ---
#define WIFI_SSID      "FRITZ!Repeater 3000"
#define WIFI_PASSWORD  "shamballa"

// --- PIN ---
#define PIN_RELAY      5     // D1 - relè sirena (ACTIVE HIGH)
#define PIN_DOOR       4     // D2 - sensore NC porta

// Durata ciclo sirena
#define SIREN_DURATION 180000   // 3 minuti
#define MAX_CYCLES 3 

// --- BLYNK VIRTUAL PINS ---
#define VPIN_ALARM     V0
#define VPIN_SIREN     V1
#define VPIN_DOOR      V2
#define VPIN_LOG       V3
#define VPIN_SIREN_STATUS  V4 
#define VPIN_ALARM_TRIGGERED V5

// --- LOG EVENTS NAMES ---
#define EVT_ALARM_ON            "alarm_on"
#define EVT_ALARM_OFF           "alarm_off"
#define EVT_TRIGGER             "alarm_triggered"
#define EVT_AUTO_OFF            "auto_sirena_off"
#define EVT_NEXT_CYCLE          "sirena_next_cycle"


#endif
