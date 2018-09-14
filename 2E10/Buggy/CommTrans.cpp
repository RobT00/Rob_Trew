#include "CommTrans.h"

#include "Arduino.h"

void CommTrans::writeXbee(String command) const {
  Serial.print(my_ID);
  Serial.print(" ");
  Serial.print(0);
  Serial.print(" ");
  Serial.print(command);
  Serial.print('\n');
  Serial.flush();
}

void CommTrans::processCommand(char c) {
  // If command not finished, simply add `c` to the input buffer
  if (c != '\n') {
    message += c;
    return;
  }

  // Extract IDs and command and filter
  if (message.length() < 5) {
    message = "";
    return;
  }

  short send_ID = message[0] - '0';
  short reci_ID = message[2] - '0';
  String command = message.substring(4);
  message = "";

  if (send_ID != 0) {
    return;
  }
  if (reci_ID != my_ID) {
    return;
  }

  // Acknowledge the recept of the command
  if (command != "ACK") {
    writeXbee("ACK");
  }

  // Execute command handler, or the default handler if none exist
  VoidFunction f = handlers.get(command);
  if (f != NULL) {
    f();
  } else if (defaultHandler != NULL) {
    defaultHandler(command);
  }
}

void CommTrans::init() const {
  Serial.begin(9600);
  Serial.print("+++");
  delay(1500);
  Serial.println("ATID 3308, CH C, CN");
  delay(11000); // Wait for AT mode to exit
  while (Serial.read() != -1) {} // Discard OKs
}

void CommTrans::addHandler(String command, VoidFunction handler) {
  handlers.add(command, handler);
}

void CommTrans::setDefaultHandler(StringVoidFunction handler) {
  defaultHandler = handler;
}
