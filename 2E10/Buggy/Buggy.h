#pragma once

#include "CommTrans.h"
#include "MotorControls.h"

#include <Arduino.h>

enum Direction {
  CLOCKWISE,
  ANTI_CLOCKWISE
};

/** Coordinates the operation of the buggy */
class Buggy {
 private:
  enum ParkingState {
    NOT_PARKING,
    BEFORE_INTERSECTION,
    AFTER_INTERSECTION
  };
  ParkingState parkingState = NOT_PARKING;
  const unsigned int parking_overrideOffAt = 3000; // ms
  const unsigned int parking_stopAt = 6500; // ms

  const CommTrans *comms;
  MotorControls *motor;

  /** Whether the buggy is instructed to go by the station */
  bool going = false;
  Direction travelDirection;

  /**
   * The number of milliseconds for which the motors have been on until the last
   * call to `go()`
   */
  unsigned long travelledTime = 0l; // ms
  /** Timestamp of last call to `go()` */
  unsigned long lastGoTime = 0l; // ms

  /** If true, an IR interrupt has happened and should be processed */
  volatile bool irInterrupt = false;
  /** If true, disregard any IR interrupts */
  volatile bool underGantry = false;
  /** Timestamp in travelled time storing when the last gantry was reached */
  unsigned long atGantryAt = 0l; // ms

  /** Checks and processes a potential IR interrupt */
  void detectGantry();
  /** Executes parking */
  void updateParking();
  /** Read the length of the gantry pulse */
  int readGantry() const; // ms
  /**
   * Calculates the number of milliseconds for which the motors have been on
   * since the last gantry
  */
  unsigned long timeTravelledSinceGantry() const; // ms

 public:
  /** Pin used for gantry detection */
  static const short IR_PIN = 2;

  Buggy() = delete;
  Buggy(short ID, MotorControls *m, CommTrans *c) : motor(m), comms(c) {
    pinMode(IR_PIN, INPUT);
    motor->stop();
    if (ID == 1) {
      travelDirection = CLOCKWISE;
    } else {
      travelDirection = ANTI_CLOCKWISE;
    }
  }

  /** `silent`: if true, no GOING is sent to the station */
  void go(bool silent = false);
  /** `silent`: if true, no STOPPED is sent to the station */
  void stop(bool silent = false);
  /** Sets the flag that the buggy should be parked by `updateParking()` */
  void park();
  bool isGoing() const { return going; }

  Direction getDirection() const { return travelDirection; }
  void setDirection(Direction d) { travelDirection = d; }

  /** To be called every time in `loop()` */
  void update();
  /** Interrupt handler for the IR interrupt */
  void gantry_ISR();

  /**
   * Calculates the number of milliseconds for which the motors have been on
   * since the buggy has been turned on
   */
  unsigned long getTravelledTime() const;
};
