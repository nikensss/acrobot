#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

class Joystick
{
public:
  Joystick(uint8_t pin, bool inverted);
  int16_t getValue();

private:
  uint32_t lastReadingTime;
  int16_t lastValue;
  uint8_t pin;
  bool inverted;
};

#endif
