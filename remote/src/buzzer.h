#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
private:
  uint32_t timer = 0;

public:
  void update();
  void set(uint16_t time);
};

#endif
