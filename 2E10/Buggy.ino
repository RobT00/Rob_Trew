#include "CommTrans.h"
#include "Buggy.h"
#include "UltraSonic.h"
#include "Lights.h"

CommTrans *comm;
MotorControls *motors;
Buggy *buggy;
UltraSonic *sonic;
Lights *christmasTree;

void setup() {
  short buggyID = 1;

  motors = new MotorControls();

  christmasTree = new Lights();
  christmasTree->setMotor(motors);

  comm = new CommTrans(buggyID);
  comm->init();
  comm->setDefaultHandler( [] (const String & command) { comm->writeXbee("INVALID: " + command); });
  comm->addHandler("PING", [] { comm->writeXbee("PONG"); });
  comm->addHandler("PONG", [] { comm->writeXbee("PING"); });
  comm->addHandler("SYN",  [] { });
  comm->addHandler("GO",   [] { buggy->go(); });
  comm->addHandler("STOP", [] { buggy->stop(); });
  comm->addHandler("PARK", [] { buggy->park(); });

  buggy = new Buggy(buggyID, motors, comm);
  attachInterrupt(digitalPinToInterrupt(Buggy::IR_PIN), IR_ISR, RISING);

  sonic = new UltraSonic(buggy, comm);
  christmasTree->setUltrasonic(sonic);
}

void loop() {
  buggy->update();
  sonic->ultraLoop();
  christmasTree->update();
}

void serialEvent() {
  while (Serial.available()) {
    char message = Serial.read();
    comm->processCommand(message);
  }
}

/** Interrupt handler has to be a non-member C function */
void IR_ISR() {
  buggy->gantry_ISR();
}
