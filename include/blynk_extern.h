#ifndef BLYNK_EXTERN_H
#define BLYNK_EXTERN_H

#include "blynk_handlers.h"

// Prevent the Blynk headers from creating a global `Blynk` instance
// in every translation unit that includes this header.
#define NO_GLOBAL_BLYNK
#include <BlynkSimpleEsp8266.h>

extern BlynkWifi Blynk;
extern BlynkTimer timer;

#endif