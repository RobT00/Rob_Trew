#include <Arduino.h>

#include "MotorControls.h"
#include "UltraSonic.h"

/** Drives the LED indicators */
class Lights {
 public:
  Lights();
  /** Set the MotorControls instance to be queried */
  void setMotor(const MotorControls *);
  /** Set the UltraSonic instance to be queried */
  void setUltrasonic(const UltraSonic *);
  /** Should be called in `loop()` */
  void update();

 private:
  const MotorControls* motor_;
  const UltraSonic* ultra_;

  /** Duration of the loop of the red LEDs */
  static const int16_t loopDuration; // ms
  /** Period of indicator flashing */
  static const int16_t indicatorPeriod; // ms

  static const int8_t leftIndicatorPin;
  static const int8_t rightIndicatorPin;
  static const int8_t nPins;
  static const int8_t pins[];

  // Have to use non-intuitive polarities if using an NPN emitter follower
  void setLightState(uint8_t pin, bool on) const { digitalWrite(pin, on ? LOW : HIGH); }
  void on(uint8_t pin) const { setLightState(pin, true); }
  void off(uint8_t pin) const { setLightState(pin, false); }
};
