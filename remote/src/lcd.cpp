#include <lcd.h>

Lcd::Lcd(PhysicalSwitch &lowPowerSwitch, Battery &battery)
    : lowPowerSwitch(lowPowerSwitch), battery(battery), liquidCrystal(0x27, 20, 4)
{
  updateTimer = millis();
}

void Lcd::init()
{
  liquidCrystal.init();
  liquidCrystal.clear();
  liquidCrystal.backlight();
}

void Lcd::allModesOff()
{
  liquidCrystal.clear();
  for (uint8_t i = 0; i < NUM_MODES - 1; i++)
  {
    turnModeOff(static_cast<Mode>(i));
  }
  
}

void Lcd::turnModeOn(Mode mode)
{
  modeStates[mode] = true;
  liquidCrystal.clear();
  writeStaticData();
}

void Lcd::turnModeOff(Mode mode)
{
  modeStates[mode] = false;
  liquidCrystal.clear();
  writeStaticData();
}

void Lcd::update()
{
  if (shouldWakeUp()){
    init();
    writeStaticData();
  }

  if (updateTimer > millis()) return;

  updateTimer = millis() + 200; // only draw on lcd every 200ms
  writeDynamicData();

}

void Lcd::writeStaticData()
{
  if (modeStates[REMOTE_MODE_NAME]){
    // liquidCrystal.setCursor(0, 0);
    // if (remoteMode == poseMode) // todo: reference remote data
    // {
    //   liquidCrystal.print("Pose mode");
    // }
    // if (remoteMode == sliderMode)
    // {
    //   liquidCrystal.print("Slider mode");
    // }
    // if (remoteMode == moveMode)
    // {
    //   liquidCrystal.print("Move mode");
    // }
  }

  if (modeStates[JOYSTICK])
  {
    liquidCrystal.setCursor(0, 0);
    liquidCrystal.print("JLX: ");
    liquidCrystal.setCursor(0, 1);
    liquidCrystal.print("JLY: ");
    liquidCrystal.setCursor(0, 2);
    liquidCrystal.print("JRX: ");
    liquidCrystal.setCursor(0, 3);
    liquidCrystal.print("JRY: ");
  }
  // if (modeStates[SLIDER]){
    
  // }
  if (modeStates[PID])
  {
    // liquidCrystal.setCursor(0, 3);

    // if (encoderPIDSelection == 0) // todo: reference encoder NO, MODE&STATE
    // {
    //   liquidCrystal.print("P=     i:     d:");
    // }
    // if (encoderPIDSelection == 1)
    // {
    //   liquidCrystal.print("p:     I=     d:");
    // }
    // if (encoderPIDSelection == 2)
    // {
    //   liquidCrystal.print("p:     i:     D=");
    // }
  }

  if (modeStates[TARGET_POSITION]){
    liquidCrystal.setCursor(0, 0);
    liquidCrystal.setCursor(0, 1);
    liquidCrystal.print("tR:     tL:");
    liquidCrystal.setCursor(0, 2);
    liquidCrystal.print("pR:     pL:");
  }
  // if (modeStates[BATTERY]){
  
  // }

}

void Lcd::writeDynamicData()
{
  // if (modeStates[REMOTE_MODE_NAME]){

  // }

  if (modeStates[JOYSTICK])
  {
    // char joyLX[5]; // amount of characters in string + 1
    // char joyLY[5];
    // char joyRX[5];
    // char joyRY[5];

    // // %04d = 4 digit string with leading zeros
    // sprintf(joyLX, "%04d", dataOut.joystickLX); // todo: get joystick data
    // sprintf(joyLY, "%04d", dataOut.joystickLY); 
    // sprintf(joyRX, "%04d", dataOut.joystickRX);
    // sprintf(joyRY, "%04d", dataOut.joystickRY);

    // liquidCrystal.setCursor(4, 0);
    // liquidCrystal.print(joyLX);
    // liquidCrystal.setCursor(4, 1);
    // liquidCrystal.print(joyLY);
    // liquidCrystal.setCursor(4, 2);
    // liquidCrystal.print(joyRX);
    // liquidCrystal.setCursor(4, 3);
    // liquidCrystal.print(joyRY);
  }
  if (modeStates[SLIDER]){
    // char slideLLeg[6]; // amount of characters in string + 1
    // char slideLArm[6];
    // char slideRLeg[6];
    // char slideRArm[6];

    // // %05d 5 digit string with leading zeros
    // sprintf(slideLLeg, "%05d", dataOut.sliderLL); // todo: reference slider
    // sprintf(slideLArm, "%05d", dataOut.sliderLA); 
    // sprintf(slideRLeg, "%05d", dataOut.sliderRL);
    // sprintf(slideRArm, "%05d", dataOut.sliderRA);

    // // print ads
    // liquidCrystal.setCursor(9, 0);
    // liquidCrystal.print(slideLLeg);
    // liquidCrystal.setCursor(9, 1);
    // liquidCrystal.print(slideLArm);
    // liquidCrystal.setCursor(9, 2);
    // liquidCrystal.print(slideRLeg);
    // liquidCrystal.setCursor(9, 3);
    // liquidCrystal.print(slideRArm);
  }

  if (modeStates[PID])
  {
    // liquidCrystal.setCursor(2, 3);
    // liquidCrystal.print(kP, 1); // todo: reference pid
    // liquidCrystal.setCursor(9, 3);
    // liquidCrystal.print(kI, 1);
    // liquidCrystal.setCursor(16, 3);
    // liquidCrystal.print(kD, 1);
  }
  if (modeStates[TARGET_POSITION]){
    // liquidCrystal.setCursor(3, 1);
    // liquidCrystal.print(rTargetPositionDegrees); // todo: reference target positions
    // liquidCrystal.print(" ");
    // liquidCrystal.setCursor(3, 2);
    // liquidCrystal.print(dataIn.rInput, 0); // reference motor encoders
    // liquidCrystal.print(" ");

    // liquidCrystal.setCursor(11, 1);
    // liquidCrystal.print(lTargetPositionDegrees);
    // liquidCrystal.print(" ");
    // liquidCrystal.setCursor(11, 2);
    // liquidCrystal.print(dataIn.lInput, 0);
    // liquidCrystal.print(" ");
  }

  if (modeStates[BATTERY]){
    liquidCrystal.setCursor(18, 0);
    char batPerc[3];
    sprintf(batPerc, "%02d", battery.getPercentage());
    liquidCrystal.print(batPerc);
  }
}

bool Lcd::shouldWakeUp(){
  return lowPowerSwitch.isOff() && lowPowerSwitch.hasChanged();
}