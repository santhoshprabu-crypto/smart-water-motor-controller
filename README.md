# Smart Water Motor Controller

Control a water pump from your own web app. An ESP32 receives the command through the Blynk cloud and switches a relay, with a safety timer and a manual backup button.

I live on the second floor and the motor switch is downstairs. I built this so I don't have to walk down every time the tank needs filling, and so the motor can't run forever if I forget it.

> **Status:** tested in the [Wokwi](https://wokwi.com) simulator. A real hardware version is next.

## Demo

- Demo video: *add your LinkedIn post link here*
- Wokwi project: *add the link here after removing your token from the code*

![App screenshot](screenshots/app.png)
![Circuit screenshot](screenshots/circuit.png)

## How it works

```
Web app  ->  Blynk cloud  ->  ESP32  ->  Relay  ->  Motor
```

1. I tap the tank button in the web app (`index.html`).
2. The app sends the command to the Blynk cloud API (virtual pin `V0`).
3. The ESP32 receives it and switches the relay.
4. The app shows live status: device online/offline, motor running or stopped, and running time.

## Features

- Remote ON/OFF from my own web app (the tank fills when the motor runs)
- Live device status (online/offline) and running time
- Auto shut-off safety timer (10 seconds in the demo, change `MAX_RUN_MS` for real use)
- Manual push button as backup, and the app stays in sync
- Motor always starts OFF after a reboot or power cut

## Tech used

- ESP32, C++ (Arduino framework)
- Blynk Cloud (virtual pin V0, REST API)
- HTML, CSS, JavaScript (single file, no frameworks)
- Wokwi simulator

## Circuit (Wokwi)

| Part | ESP32 pin |
|---|---|
| Relay module IN | GPIO 26 |
| Push button | GPIO 25 and GND |
| Relay VCC / GND | VIN (5V) / GND |
| LED (shows the "motor") | Relay COM/NO through a 220 ohm resistor |

## Setup

1. **Blynk:** create a template named `Water motor` (ESP32, WiFi). Add a datastream: virtual pin `V0`, type Integer, min 0, max 1. Add a Switch widget linked to `V0`. Create a device from the template.
2. **ESP32 code:** open `esp32_water_motor.ino` and replace `YOUR_TEMPLATE_ID` and `YOUR_AUTH_TOKEN` with your own values. Add the `Blynk` library. In Wokwi, the WiFi is `Wokwi-GUEST` with no password.
3. **Region:** the code uses `blr1.blynk.cloud`. Change it (in both the `.ino` and `index.html`) if your Blynk region is different.
4. **Web app:** open `index.html` in a browser, paste your Auth Token, and press Connect. The token is saved only in your browser.

## Safety notes

- **Never upload your real Auth Token to GitHub.** If you do by mistake, regenerate it in Blynk.
- The mains side (contactor and motor wiring) should be done by a qualified electrician. This project is tested in simulation only.
- Keep a physical backup switch and a max run timer in any real installation.

## What I learned

- Connecting an ESP32 to a cloud service
- Debugging wrong configs (template values, server region)
- Designing safety features: auto shut-off and safe state after a power cut
- Building a small web app that talks to an IoT API

## Next steps

- Automatic mode with a tank water level sensor
- Dry-run protection for an empty sump
- Notifications ("tank full", "motor running too long")
- Tamil language support
- Real hardware version

## Author

Santhosh, first-year student. Open to feedback from the IoT and embedded community.
