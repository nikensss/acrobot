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
  Battery(Buzzer &buzzer, PhysicalSwitch &lowPowerSwitch);
  bool shouldSleep();
  void sleep();
  bool shouldWakeUp();
  void wakeUp();
  bool shouldBuzzerBuzz();
  void update();
  int8_t getPercentage();

private:
  Buzzer &buzzer;
  PhysicalSwitch &lowPowerSwitch;
  RunningMedian samples;
  uint32_t alarmTimer;
  int8_t percentage;
};

#endif
