#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H


#include <Arduino.h>
#include <PID_v1.h> // https://github.com/br3ttb/

class MotorController {
public:
  MotorController(uint8_t forwardPwmChannel, uint8_t backwardPwmChannel,
                  uint16_t range, uint8_t deadBand, Encoder &encoder);
  void update();

  void setTarget(double target);
  void setKp(double Kp);
  void setKi(double Ki);
  void setKd(double Kd);

  double getTarget();
  double getKp();
  double getKi();
  double getKd();

private:
  uint8_t forwardPwmChannel, backwardPwmChannel, deadBand;
  uint16_t range;
  double pidTarget, pidInput, pidOutput;
  // Kp = proportional gain, Ki = integral gain, Kd = derivative gain
  double Kp = 1, Ki = 0, Kd = 0;

  Encoder &encoder;
  PID pid;

  void updatePid();
  void updateMotor();
};

#endif
