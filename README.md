# ESP8266 Home Alarm System (Blynk)

This project is a **modular home alarm system** built around an **ESP8266 (WeMos D1 mini / Pro)** and the **Blynk IoT platform**.

The system is designed with **clean separation of responsibilities**, making it easy to maintain, debug, and extend in the future.

---

## 🔐 Features

- ✅ Door sensor monitoring (NC contact)
- 🚨 Siren control via relay
- 📱 Full control and monitoring via **Blynk App & Web Dashboard**
- 🔁 Alarm re-trigger logic with **maximum cycle limit**
- ⏱ Automatic siren timeout (3-minute cycles)
- 🛑 Manual siren stop from the app
- 🔄 Correct re-arming behavior after manual stop or door close
- 📊 Virtual LED indicators for:
  - Door status
  - Siren status
  - Alarm triggered state
- 📜 Event logging via Blynk Events

---

## 🧠 Alarm Logic Overview

1. Alarm is **armed** via Blynk (V0)
2. Door opens → **siren activates**
3. Siren runs for **3 minutes**
4. If door remains open:
   - Siren can restart for up to **MAX_CYCLES**
5. After reaching max cycles:
   - Siren stops permanently until manually reset
6. Siren can always be stopped manually from the app
7. After door closure, the system **correctly re-arms itself**

---

## 🛠 Hardware Requirements

ESP8266 (WeMos D1 Mini / D1 Mini Pro)
Door sensor (NC contact)
Relay module (active HIGH)
Siren or buzzer
Stable WiFi connection

---

## 📲 Blynk Setup

Virtual pins used:

Function	Virtual Pin
Alarm Arm/Disarm	V0
Siren Stop (Push)	V1
Door Sensor LED	V2
Siren Status LED	V4
Alarm Triggered LED	V5

---

Known Limitations / TODO

🚧 Not implemented yet (by design):

- WiFi connection watchdog
- LED indicator for WiFi connectivity
- Notifications when WiFi connection is lost
- Offline/fail-safe behavior without network

## 🧩 Project Structure

```text
├── include
│   ├── alarm_state.h      # Shared alarm state and flags
│   ├── config.h           # Pins, Blynk settings, constants
│
├── src
│   ├── main.cpp           # Setup, loop, WiFi, timers
│   ├── alarm.cpp          # Siren logic and timing
│   ├── door.cpp           # Door sensor handling
│   ├── blynk_handlers.cpp # Blynk virtual pin handlers
│   ├── ota.cpp            # OTA update support
│
├── platformio.ini
└── README.md
