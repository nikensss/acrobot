#ifndef PHYSICAL_SWITCH_H
#define PHYSICAL_SWITCH_H

#include <Arduino.h>

class PhysicalSwitch
{
public:
  PhysicalSwitch(uint8_t pin, uint8_t mode);
  bool hasChanged();
  bool isOn();
  bool isOff();
  void update();

private:
  uint pin;
  bool currentState;
  bool previousState;
};

#endif