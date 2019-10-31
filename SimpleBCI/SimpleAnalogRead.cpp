
#include "SimpleAnalogRead.h"

SimpleAnalogRead::SimpleAnalogRead(){
    setAll(1000,10,34,6000);
}

void SimpleAnalogRead::setAll(
  int sampleInterval, int tolerance,
  int pin, int memSize){

  alreadyRead=false;
  address=0;
  this->sampleInterval=sampleInterval;
  this->tolerance=tolerance;
  this->pin=pin;
  this->memSize=memSize;
  messagePrefix= String("analogRead:{")
    +"\"pin\":"+String(pin)
    +",\"values\":[";
}

void SimpleAnalogRead::runRoutine(){
  int reminder = micros()%sampleInterval;
  if((reminder<tolerance
    || reminder>sampleInterval-tolerance)
    && !alreadyRead ){
    read(); alreadyRead = true;
  }
  else{
    alreadyRead = false;
  }
}

void SimpleAnalogRead::read(){
  buffer[address]=analogRead(pin);
  if(address==memSize-1){
    send();
    address=0;
  }
  else address++;
}

void SimpleAnalogRead::send(){
  String message=messagePrefix;
  for(int i=0;i<memSize-1;i++){
    message+=(String(buffer[i])+",");
  }
  message+=(String(buffer[memSize-1])+"]}");
  analogReadWantsToBroadcastTXT(message);
}
