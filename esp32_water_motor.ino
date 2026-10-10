// Water Motor Controller - Wokwi version
// Button (pin 25) + Phone app (Blynk V0) -> Relay (pin 26)
// NOTE: put your own Blynk credentials below. Never upload real ones to GitHub.

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Water motor"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const int  RELAY_PIN  = 26;
const int  BUTTON_PIN = 25;
const bool RELAY_ACTIVE_LOW = false;        // Wokwi relay: HIGH = ON
const unsigned long MAX_RUN_MS = 10000;     // 10 seconds for testing (use 30 min in real life)

bool motorOn = false;
unsigned long motorStartMs = 0;

bool lastButton = HIGH;
unsigned long lastPressMs = 0;

void setMotor(bool on) {
  motorOn = on;
  if (on) motorStartMs = millis();
  digitalWrite(RELAY_PIN, (on == RELAY_ACTIVE_LOW) ? LOW : HIGH);
  Serial.println(on ? "Motor ON" : "Motor OFF");
}

// Phone app switch (V0)
BLYNK_WRITE(V0) {
  setMotor(param.asInt() == 1);
}

// When the app connects, show the real motor state
BLYNK_CONNECTED() {
  Blynk.virtualWrite(V0, motorOn ? 1 : 0);
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  setMotor(false);   // always start OFF
  Blynk.begin(BLYNK_AUTH_TOKEN, "Wokwi-GUEST", "", "blr1.blynk.cloud", 80);
}

void loop() {
  Blynk.run();

  // Manual button: each press toggles the motor
  bool reading = digitalRead(BUTTON_PIN);
  if (reading != lastButton && millis() - lastPressMs > 50) {
    lastPressMs = millis();
    lastButton = reading;
    if (reading == LOW) {                       // button pressed
      setMotor(!motorOn);
      Blynk.virtualWrite(V0, motorOn ? 1 : 0);  // update the app too
    }
  }

  // Safety timer: auto-stop after max run time
  if (motorOn && millis() - motorStartMs >= MAX_RUN_MS) {
    setMotor(false);
    Blynk.virtualWrite(V0, 0);
    Serial.println("Timer finished, motor stopped");
  }
}
