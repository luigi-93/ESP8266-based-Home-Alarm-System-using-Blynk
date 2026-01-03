#pragma once
#include <Arduino.h>

enum AlarmMode {
  DISARMED = 0,
  ARMED = 1
};

struct AlarmState {
  AlarmMode mode = ARMED;
  bool sirenOn = false;
  bool doorOpen = false;

  unsigned long sirenStartTime = 0;
  int cycles = 0;

  bool manualSirenOff = false;    // STOP manuale sirena
  bool alarmTriggered = false;   // ⭐ evento porta già gestito
};

extern AlarmState alarm;

