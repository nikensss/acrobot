#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <physicalSwitch.h>
#include <battery.h>

class Lcd
{
public:
  Lcd(PhysicalSwitch &lowPowerSwitch, Battery &battery);
  void init();
  void allModesOff(); 
  enum Mode { REMOTE_MODE_NAME, JOYSTICK, SLIDER, PID, TARGET_POSITION, BATTERY, NUM_MODES};
  void turnModeOn(Mode mode); 
  void turnModeOff(Mode mode);
  void update();


private:
  PhysicalSwitch &lowPowerSwitch;
  Battery &battery;
  LiquidCrystal_I2C liquidCrystal;
  uint32_t updateTimer;
  bool modeStates[NUM_MODES];

  void writeStaticData();
  void writeDynamicData();
  bool shouldWakeUp();
};

#endif
