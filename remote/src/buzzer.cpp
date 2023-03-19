#include <buzzer.h>

Buzzer::Buzzer(uint8_t pin) : pin(pin)
{
  pinMode(pin, OUTPUT);
}

void Buzzer::update()
{
  digitalWrite(pin, timer > millis());
}

void Buzzer::buzzFor(uint16_t ms)
{
  timer = millis() + ms;
}
