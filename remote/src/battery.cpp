#include "battery.h"

#define BATTERY_V 35

Battery::Battery(Buzzer &buzzer, PhysicalSwitch &lowPowerSwitch)
    : buzzer(buzzer), lowPowerSwitch(lowPowerSwitch), samples(64)
{
  alarmTimer = millis();
}

void Battery::sleep()
{
  WiFi.setSleep(true);
  setCpuFrequencyMhz(80);
  Serial.println("sleep mode enabled");
}

void Battery::wakeUp()
{
  WiFi.setSleep(false);
  setCpuFrequencyMhz(240);
  Serial.println("sleep mode disabled");
}

bool Battery::shouldSleep()
{
  return lowPowerSwitch.isOn() && lowPowerSwitch.hasChanged();
}

bool Battery::shouldWakeUp()
{
  return lowPowerSwitch.isOff() && lowPowerSwitch.hasChanged();
}

bool Battery::shouldBuzzerBuzz()
{
  return getPercentage() < 10 && alarmTimer < millis() && lowPowerSwitch.isOff();
}

int8_t Battery::getPercentage()
{
  // 2060 =~ 3.65v, 2370 =~ 4.2v
  return percentage;
}

void Battery::update()
{
  samples.add(analogRead(BATTERY_V));
  // 2060 =~ 3.65v, 2370 =~ 4.2v
  percentage = map(samples.getAverage(), 2060, 2370, 0, 100);

  if (shouldSleep())
  {
    sleep();
  }

  if (shouldWakeUp())
  {
    wakeUp();
    // lcd.init();
    // lcd.clear();
    // setLCD();
  }

  if (shouldBuzzerBuzz())
  {
    buzzer.buzzFor(300);
    alarmTimer = millis() + 600;
  }
}
