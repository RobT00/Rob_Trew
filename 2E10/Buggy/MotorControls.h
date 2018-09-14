#pragma once

enum MotorState {
  STOPPED,
  GOING,
  LEFT_OVERRIDE,
  RIGHT_OVERRIDE
};

class MotorControls {
 private:
  static const short bcc_pin = 3;

  MotorState state = STOPPED;

  void write(short duration) const;

 public:
  MotorControls();
  void leftOverride();
  void rightOverride();
  void go();
  void stop();
  void fullPower();
  MotorState getState() const;
};
