#include "UltraSonic.h"

#include "Arduino.h"

void UltraSonic::ultraLoop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastPingTime >= pingInterval) {
    lastPingTime = currentMillis;
    unsigned long distance = measureDistance();
    if (obstacle == false && distance < tresholdDistance && buggy->isGoing()) { // New obstacle
      buggy->stop();
      comms->writeXbee("OBSTACLE");
      obstacle = true;
    } else if (obstacle == true && distance > tresholdDistance) { // Obstacle gone
      comms->writeXbee("PATHCLEAR");
      obstacle = false;
    }
  }
}

unsigned long UltraSonic::measureDistance() const {
  // Request ultrasonic pulse
  pinMode(ultraPin, OUTPUT);
  digitalWrite(ultraPin, LOW);
  digitalWrite(ultraPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraPin, LOW);

  // Recieve distance data
  pinMode(ultraPin, INPUT);
  unsigned long pulseLength = pulseIn(ultraPin, HIGH, maxPulseLength);
  if (pulseLength == 0) {
    pulseLength = maxPulseLength;
  }

  // Calculate distance
  double distance = ((pulseLength / 2) * .03432);
  return (unsigned long) distance;
}
