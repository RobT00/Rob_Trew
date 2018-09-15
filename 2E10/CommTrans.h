#pragma once

#include "HashMap.h"
#include "Functions.h"

#include <Arduino.h>

/** Handles Serial communication */
class CommTrans {
 public:
  CommTrans() = delete;
  CommTrans(short ID) : my_ID(ID) {}

  /** Initialise the Xbee with the correct channel */
  void init() const;

  /** Send command through Serial */
  void writeXbee(String command) const;

  /** Process incoming character */
  void processCommand(char c);

  /** Add function to handle the given command */
  void addHandler(String command, VoidFunction handler);
  void setDefaultHandler(StringVoidFunction handler);

 private:
  /** The input buffer */
  String message; // Input buffer

  /** A map of the command handlers */
  HashMap handlers;
  StringVoidFunction defaultHandler = NULL;

  const short my_ID;
};
