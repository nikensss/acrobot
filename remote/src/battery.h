#ifndef BATTERY_H
#define BATTERY_H

#include "buzzer.h";

class Battery {
public:
  Battery(Buzzer &buzzer, RunningMedian &samples, int8_t percent);
  void sleep();
  void awake();
  void update();

private:
  Buzzer &buzzer;
  RunningMedian samples;
  int8_t percent;
  bool isCharging;
  uint32_t alarmTimer;
};

#endif
