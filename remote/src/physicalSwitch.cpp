#include <physicalSwitch.h>

PhysicalSwitch::PhysicalSwitch(uint8_t pin, uint8_t mode) : pin(pin)
{
  pinMode(pin, mode);
  currentState = digitalRead(pin);
  previousState = currentState;
}

bool PhysicalSwitch::hasChanged()
{
  return currentState != previousState;
}

bool PhysicalSwitch::isOn()
{
  return currentState;
}

bool PhysicalSwitch::isOff()
{
  return !currentState;
}

void PhysicalSwitch::update()
{
  previousState = currentState;
  currentState = digitalRead(pin);
}
