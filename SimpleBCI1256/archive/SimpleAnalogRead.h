
#ifndef SimpleAnalogRead_h
#define SimpleAnalogRead_h

#include <Arduino.h>

void analogReadWantsToBroadcastTXT(String message);

class SimpleAnalogRead{
private:
  int sampleInterval;
  int pin, memSize;
  bool alreadyRead;
  int address;
  int myBuffer[2000];
  unsigned long sampleTimeAxis[2000];
  String messagePrefix;

  void send();
  //void read();
public:
  SimpleAnalogRead();
  void setAll(
    int sampleInterval, int pin, int memSize);
  void runRoutineBlocking();
  //void runRoutine();
};

#endif
