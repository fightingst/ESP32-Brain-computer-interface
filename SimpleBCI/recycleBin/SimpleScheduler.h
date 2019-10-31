
#ifndef SimpleScheduler_h
#define SimpleScheduler_h

#include <Arduino.h>

void doEachMicroSec();
void doEach10MicroSec();
void doEach100MicroSec();
void doEachMilliSec();
void doEach10MilliSec();
void doEach100MilliSec();
void doEachSec();

class SimpleScheduler{
private:
  int dt;
  unsigned long lastMicros;
public:
  SimpleScheduler(int tolerance);
  void watch();
};

#endif
