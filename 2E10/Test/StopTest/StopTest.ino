#include "MotorControls.h"

void setup()
{
  delay(1000);
  MotorControls motor;
  motor.go();
  motor.fullPower();
  delay(500);
  motor.halfPower();
  delay(500);
  motor.reducePower();
  motor.reducePower();
  motor.reducePower();
  delay(100);
  motor.stop();
}

void loop() { }
