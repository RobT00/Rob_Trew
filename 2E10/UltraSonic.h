#pragma once

#include "Buggy.h"
#include "CommTrans.h"

#include "Arduino.h"

class UltraSonic {
 private:
  Buggy* buggy;
  const CommTrans* comms;

  const unsigned short groundPin = 16;
  const unsigned short powerPin = 17;
  const unsigned short ultraPin = 18;
  const unsigned long tresholdDistance = 14; // cm 
  //used 14 for buggy1 and 13 for buggy2
  const unsigned long pingInterval = 400; // ms
  /** Timestamp of the previous ping */
  unsigned long lastPingTime = 0; // ms
  /** Maximum length of a pulse sent from the sensor */
  const unsigned long maxPulseLength = 40000; // micros

  /** True if there is an obstacle in front of the buggy */
  bool obstacle = false;

  /** Measure how far the obstacle is, if any */
  unsigned long measureDistance() const;

 public:
  UltraSonic(Buggy* b, CommTrans* c) : buggy(b),
                                       comms(c) {
    pinMode(groundPin, OUTPUT);
    pinMode(powerPin, OUTPUT);
    digitalWrite(groundPin, LOW);
    digitalWrite(powerPin, HIGH);
  }

  /** Should be called in the `loop()` every time */
  void ultraLoop();

  bool isBlockedByObstacle() const { return obstacle; }
};
