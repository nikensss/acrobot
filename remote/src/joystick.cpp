#include <joystick.h>

Joystick::Joystick(uint8_t pin, bool inverted) 
    : pin(pin), inverted(inverted)
{
  lastReadingTime = 0;
}

int16_t Joystick::getValue()
{
  if (millis() - lastReadingTime > 1){
    lastReadingTime = millis();
    if (inverted)
    {
      lastValue = 4095 - analogRead(pin);   
    } 
    else 
    {
      lastValue = analogRead(pin);
    }
  }

  return lastValue;
}