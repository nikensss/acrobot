#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include <physicalSwitch.h>
#include <RunningMedian.h>
#include <WiFi.h>
#include <buzzer.h>

class Battery
{
public:
  Battery(uint8_t pin, Buzzer &buzzer, PhysicalSwitch &lowPowerSwitch);
  void update();
  int8_t getPercentage();

private:
  uint8_t pin;
  Buzzer &buzzer;
  PhysicalSwitch &lowPowerSwitch;
  RunningMedian samples;
  uint32_t alarmTimer;
  int8_t percentage;
  bool shouldSleep();
  bool shouldWakeUp();
  bool shouldBuzzerBuzz();
  void sleep();
  void wakeUp();
};

#endif
