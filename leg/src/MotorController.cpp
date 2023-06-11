#include "MotorController.h"

MotorController::MotorController(uint8_t forwardPwmChannel, uint8_t backwardPwmChannel, uint16_t range, uint8_t deadBand, Encoder &encoder) 
  : forwardPwmChannel(forwardPwmChannel), backwardPwmChannel(backwardPwmChannel), range(range), deadBand(deadBand), encoder(encoder) {
  pid = PID(&pidInput, &pidOutput, &pidTarget, Kp, Ki, Kd, DIRECT);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-range, range);
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

double MotorController::getTarget() {
  return pidTarget;
}

double MotorController::getKp() {
  return Kp;
}

double MotorController::getKi() {
  return Ki;
}

double MotorController::getKd() {
  return Kd;
}

void MotorController::updatePid() {
  pidInput = encoder.getPositionInDegrees();
  pid.Compute();
}

void MotorController::updateMotor() {
  uint16_t forwardDuty = pidOutput > 1 ? map(abs(pidOutput), 0, range, deadBand, range): 0;
  uint16_t backwardDuty = pidOutput < -1 ? map(abs(pidOutput), 0, range, deadBand, range): 0;

  ledcWrite(forwardPwmChannel, forwardDuty);
  ledcWrite(backwardPwmChannel, backwardDuty);
}

