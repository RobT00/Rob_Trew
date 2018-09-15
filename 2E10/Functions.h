#pragma once

#ifndef TEST
#include <Arduino.h>
#endif

typedef void (*VoidFunction)();
#ifndef TEST
typedef void (*StringVoidFunction)(const String &);
#endif
