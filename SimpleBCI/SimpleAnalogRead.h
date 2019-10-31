
#ifndef SimpleAnalogRead_h
#define SimpleAnalogRead_h

#include <Arduino.h>

void analogReadWantsToBroadcastTXT(String message);

class SimpleAnalogRead{
private:
  int sampleInterval, tolerance;
  int pin, memSize;
  bool alreadyRead;
  int address;
  int buffer[6000];
  String messagePrefix;
  
  void read();
  void send();
public:
  SimpleAnalogRead();
  void setAll(
    int sampleInterval, int tolerance,
    int pin, int memSize);
  void runRoutine();
};

#endif
