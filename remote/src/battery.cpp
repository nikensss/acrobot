#include "battery.h"

#define BATTERY_V 35;
#define LOW_POWER_SW 18

Battery::Battery(Buzzer &buzzer) : buzzer(buzzer) {
  samples = RunningMedian(64);
  percent = map(samples.getAverage(), 2060, 2370, 0, 100);
  isCharging = false;
  alarmTimer = millis();
}

void Battery::sleep() {
  WiFi.setSleep(true);
  setCpuFrequencyMhz(80);
  Serial.println("sleep mode enabled");
}

void Battery::awake() {
  WiFi.setSleep(false);
  setCpuFrequencyMhz(240);
  Serial.println("sleep mode disabled");
}

void Battery::update() {
  samples.add(analogRead(BATTERY_V));

  // 2060 =~ 3.65v, 2370 =~ 4.2v
  percent = map(samples.getAverage(), 2060, 2370, 0, 100);

  if (digitalRead(LOW_POWER_SW) && !isCharging) {
    isCharging = true;
    sleep();
  }

  if (!digitalRead(LOW_POWER_SW) && isCharging) {
    isCharging = false;
    awake();
    lcd.init();
    lcd.clear();
    setLCD();
  }

  if (percent < 10 && alarmTimer < millis() && !isCharging) {
    buzzer.set(300);
    alarmTimer = millis() + 600;
  }
}
