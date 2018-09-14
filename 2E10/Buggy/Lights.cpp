#include "Lights.h"

const int16_t Lights::loopDuration = 600; // ms
const int16_t Lights::indicatorPeriod = 400; // ms

const int8_t Lights::leftIndicatorPin = 5;
const int8_t Lights::rightIndicatorPin = 12;
const int8_t Lights::pins[] = {6, 7, 8, 9, 10, 11};
const int8_t Lights::nPins = 6;

Lights::Lights() {
  for (const auto &pin : pins) {
    pinMode(pin, OUTPUT);
    off(pin);
  }
  pinMode(leftIndicatorPin, OUTPUT);
  pinMode(rightIndicatorPin, OUTPUT);
  on(leftIndicatorPin);
  on(rightIndicatorPin);
}

void Lights::setMotor(const MotorControls *motor) {
  motor_ = motor;
}

void Lights::setUltrasonic(const UltraSonic *ultra) {
  ultra_ = ultra;
}

void Lights::update() {
  if (motor_ && motor_->getState() == MotorState::STOPPED) {
    for (int8_t i = 0; i < nPins; i++) {
      on(pins[i]);
    }

    const bool obstacle = (ultra_ && ultra_->isBlockedByObstacle());
    setLightState(leftIndicatorPin, obstacle);
    setLightState(rightIndicatorPin, obstacle);
  } else { // going
    // Progress of the red loop
    int16_t progress = (millis() % loopDuration) / (loopDuration / (2 * nPins));
    progress = (progress / nPins) ? (2 * nPins - 1 - progress) : progress;
    for (int8_t i = 0; i < nPins; i++) {
      setLightState(pins[i], i == progress);
    }

    off(leftIndicatorPin);
    off(rightIndicatorPin);

    // Parking indicators
    if(motor_ && motor_->getState() == MotorState::RIGHT_OVERRIDE) {
      const bool indicatorOn = (millis() % indicatorPeriod) < indicatorPeriod / 2;
      setLightState(leftIndicatorPin, indicatorOn);
      off(rightIndicatorPin);
    } else if(motor_ && motor_->getState() == MotorState::LEFT_OVERRIDE) {
      const bool indicatorOn = (millis() % indicatorPeriod) < indicatorPeriod / 2;
      off(leftIndicatorPin);
      setLightState(rightIndicatorPin, indicatorOn);
    }
  }
}
