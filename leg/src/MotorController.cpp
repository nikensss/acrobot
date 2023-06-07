#include "Motor_Controller.h"

MotorController::MotorController(uint8_t forwardPwmChannel, uint8_t backwardPwmChannel, uint16_t range, uint8_t deadBand, Encoder &encoder) 
  : forwardPwmChannel(forwardPwmChannel), backwardPwmChannel(backwardPwmChannel), range(range), deadBand(deadBand), encoder(encoder) {
  pid = PID(&pidInput, &pidOutput, &pidTarget, Kp, Ki, Kd, DIRECT);
  pid.SetMode(AUTOMATIC);
  pid.SetpidOutputLimits(-range, range);
  pid.SetSampleTime(1);
}

void MotorController::update() {
  updatePid();
  updateMotor();
}

void MotorController::setTarget(double target) {
  pidTarget = target;
}

void MotorController::setKp(double Kp) {
  this->Kp = Kp;
  pid.SetTunings(this->Kp, this->Ki, this->Kd);
}

void MotorController::setKi(double Ki) {
  this->Ki = Ki;
  pid.SetTunings(this->Kp, this->Ki, this->Kd);
}

void MotorController::setKd(double Kd) {
  this->Kd = Kd;
  pid.SetTunings(this->Kp, this->Ki, this->Kd);
}

void MotorController::updatePid() {
  pidInput = encoder.getPositionInDegrees();
  pid.Compute();
}

void MotorController::updateMotors() {
  uint16_t forwardDuty = pidOutput > 1 ? map(abs(pidOutput), 0, range, deadBand, range): 0;
  uint16_t backwardDuty = pidOutput < -1 ? map(abs(pidOutput), 0, range, deadBand, range): 0;

  ledcWrite(forwardPwmChannel, fowardDuty);
  ledcWrite(backwardPwmChannel, backwardDuty);
}

