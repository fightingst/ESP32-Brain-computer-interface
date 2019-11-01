
#include "SimpleAnalogRead.h"

SimpleAnalogRead::SimpleAnalogRead(){
    setAll(100,10,34,1000);
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
  for(int i=0;i<memSize;i++){
    sampleTimeAxis[i]=i*sampleInterval;
  }
}

void SimpleAnalogRead::runRoutineBlocking(){
  int n=0; unsigned long startTimeMicros=micros();
  while(n<memSize){
    if(micros()-startTimeMicros>sampleTimeAxis[n]){
      myBuffer[n]=analogRead(pin);
      n++;
    }
  }
  send();
}

void SimpleAnalogRead::send(){
  String message=messagePrefix;
  for(int i=0;i<memSize-1;i++){
    message+=(String(myBuffer[i])+",");
  }
  message+=(String(myBuffer[memSize-1])+"]}");
  analogReadWantsToBroadcastTXT(message);
}

/*
void SimpleAnalogRead::runRoutine(){
  int reminder = micros()%sampleInterval;
  if( reminder<tolerance && !alreadyRead ){
    read(); alreadyRead = true;
  }
  else if(reminder>tolerance){
    alreadyRead = false;
  }
}

void SimpleAnalogRead::read(){
  myBuffer[address]=analogRead(pin);
  if(address==memSize-1){
    send();
    address=0;
  }
  else address++;
}
*/
