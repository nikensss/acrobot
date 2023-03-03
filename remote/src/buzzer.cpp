#include "buzzer.h";

#define BUZZER 13

void Buzzer::update() { digitalWrite(BUZZER, timer > millis() ? HIGH : LOW); }

void Buzzer::set(uint16_t time) { timer = millis() + time; }
