void pwmInit(){
  ledcSetup(R_F_PWM_CHAN, PWM_FREQ, PWM_RES);
  ledcAttachPin(R_F_PWM_PIN, R_F_PWM_CHAN);

  ledcSetup(R_B_PWM_CHAN, PWM_FREQ, PWM_RES);
  ledcAttachPin(R_B_PWM_PIN, R_B_PWM_CHAN);

  ledcSetup(L_F_PWM_CHAN, PWM_FREQ, PWM_RES);
  ledcAttachPin(L_F_PWM_PIN, L_F_PWM_CHAN);

  ledcSetup(L_B_PWM_CHAN, PWM_FREQ, PWM_RES);
  ledcAttachPin(L_B_PWM_PIN, L_B_PWM_CHAN);
}