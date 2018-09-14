#include "Buggy.h"

void Buggy::go(bool silent) {
  if (going) {
    return;
  }
  motor->go();
  lastGoTime = millis();
  if (!silent) {
    comms->writeXbee("GOING");
  }
  going = true;
}

void Buggy::stop(bool silent) {
  if (!going) {
    return;
  }
  motor->stop();
  travelledTime += millis() - lastGoTime;
  if (!silent) {
    comms->writeXbee("STOPPED");
  }
  going = false;
}

unsigned long Buggy::getTravelledTime() const {
  if (going) {
    return travelledTime + (millis() - lastGoTime);
  } else {
    return travelledTime;
  }
}

void Buggy::gantry_ISR() {
  if (!underGantry) {
    irInterrupt = true;
  }
}

void Buggy::detectGantry() {
  if (underGantry && timeTravelledSinceGantry() > 500) {
    underGantry = false;
  }
  if (irInterrupt) {
    int gantry = readGantry();
    if (gantry == -1) {
      comms->writeXbee("GANTRY_INVALID");
      irInterrupt = false;
    } else {
      comms->writeXbee("GANTRY" + String(gantry));
      atGantryAt = getTravelledTime();
      underGantry = true;
      irInterrupt = false;
    }
  }
}

int Buggy::readGantry() const {
  while (digitalRead(IR_PIN) == HIGH) {}
  // Take the average of 2 readings for greater precision
  short count = 2;
  int sum = 0;
  for (short i = 0; i < count; i++) {
    sum += pulseIn(IR_PIN, HIGH);
  }
  int pulse = sum / count;
  comms->writeXbee(String("IRLength: ") + pulse);

  // Decide gantry ID
  if (pulse >= 500 && pulse <= 1500) {
    return 1;
  } else if (pulse >= 1500 && pulse <= 2500) {
    return 2;
  } else if (pulse >= 2500 && pulse <= 3500) {
    return 3;
  } else {
    return -1;
  }
}

unsigned long Buggy::timeTravelledSinceGantry() const {
  return getTravelledTime() - atGantryAt;
}

void Buggy::update() {
  detectGantry();
  updateParking();
}

void Buggy::updateParking() {
  if (!going) {
    return; // Do not interfere with other go-stop functionalities
  }

  if (parkingState == BEFORE_INTERSECTION) {
    if (travelDirection == CLOCKWISE && motor->getState() != LEFT_OVERRIDE) {
      motor->leftOverride();
    } else if (travelDirection == ANTI_CLOCKWISE && motor->getState() != RIGHT_OVERRIDE) {
      motor->rightOverride();
    }
  }

  unsigned long sinceGantry = timeTravelledSinceGantry();
  if (parkingState == BEFORE_INTERSECTION && sinceGantry > parking_overrideOffAt) {
    motor->go();
    parkingState = AFTER_INTERSECTION;
  } else if (parkingState == AFTER_INTERSECTION && sinceGantry > parking_stopAt) {
    stop(true);
    comms->writeXbee("PARKED");
    parkingState = NOT_PARKING;
  }
}

void Buggy::park() {
  parkingState = BEFORE_INTERSECTION;
}
