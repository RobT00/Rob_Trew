#include "MotorControls.h"

#include <Arduino.h>

MotorControls::MotorControls() {
  pinMode(bcc_pin, OUTPUT);
  digitalWrite(bcc_pin, LOW);
  delay(20);
  stop();
}

void MotorControls::write(short duration) const {
  if (duration > 20) {
    return;
  }
  digitalWrite(bcc_pin, HIGH);
  delay(duration);
  digitalWrite(bcc_pin, LOW);
  delay(20 - duration);
}

void MotorControls::leftOverride() {
  state = LEFT_OVERRIDE;
  write(6);
}

void MotorControls::rightOverride() {
  state = RIGHT_OVERRIDE;
  write(8);
}

void MotorControls::go() {
  state = GOING;
  write(4);
}

void MotorControls::stop() {
  state = STOPPED;
  write(2);
}

void MotorControls::fullPower() {
  write(18);
}

MotorState MotorControls::getState() const {
  return state;
}

