#include "ADS1256.h"

ADS1256::ADS1256(
  int CLK,int CS,int READY, int SYNC, int RESET,
  int spiSpeed, String chipId){

  setAll(1000,100);
  clk=CLK;cs=CS;dtReady=READY;sync=SYNC;reset=RESET;
  this->spiSpeed=spiSpeed; this->chipId=chipId;
  ledcSetup(0,8000000,1);//channel,frequency,resolution
  ledcAttachPin(clk,0);//pin,channel
  ledcWrite(0,1); delay(1); //channel,dutyCycle
  pinMode(cs,OUTPUT); digitalWrite(cs,LOW);
  pinMode(dtReady,INPUT);
  pinMode(sync,OUTPUT); digitalWrite(sync,HIGH);
  pinMode(reset,OUTPUT); digitalWrite(reset,LOW);
  delay(1); digitalWrite(reset,HIGH);
  spi=new SPIClass(VSPI);
  spi->begin();
  while(digitalRead(dtReady)){/*wait til LOW*/}
  spi->beginTransaction(SPISettings(spiSpeed,MSBFIRST,SPI_MODE1));
  digitalWrite(cs,LOW); delayMicroseconds(100);
  spi->transfer(0xFE); delay(5); //Reset to Power-Up Values

  byte status_reg=0x00,status_data=0x01;
  spi->transfer(0x50|status_reg);
  spi->transfer(0x00); spi->transfer(status_data);
  delayMicroseconds(100);
  byte adCtrl_reg=0x02,adCtrl_data=0x00;
  spi->transfer(0x50|adCtrl_reg);
  spi->transfer(0x00); spi->transfer(adCtrl_data);
  delayMicroseconds(100);
  byte dtRate_reg=0x03,dtRate_data=0xF0;
  spi->transfer(0x50|dtRate_reg);
  spi->transfer(0x00); spi->transfer(dtRate_data);
  delayMicroseconds(100);
  // Perform Offset and Gain Self-Calibration (F0h)
  spi->transfer(0xF0); delay(400);
  digitalWrite(cs,HIGH); spi->endTransaction();
}

void ADS1256::adcRead(int n){
  spi->beginTransaction(SPISettings(spiSpeed,MSBFIRST,SPI_MODE1));
  digitalWrite(cs,LOW);
  for(int ch=0;ch<8;ch++){
    while(digitalRead(dtReady)){}
    spi->transfer(0x50|0x01); spi->transfer(0x00);
    spi->transfer(channels[ch]); delayMicroseconds(2);
    spi->transfer(0xFC); delayMicroseconds(2);
    spi->transfer(0x00); delayMicroseconds(250);
    spi->transfer(0x01); delayMicroseconds(5);
    adcRaws[ch][n]=spi->transfer(0); adcRaws[ch][n]<<8;
    adcRaws[ch][n]=spi->transfer(0); adcRaws[ch][n]<<8;
    adcRaws[ch][n]=spi->transfer(0); delayMicroseconds(2);
    //2's complement
    if(adcRaws[ch][n]>0x7fffff) adcRaws[ch][n]-=0x1000000;
  }
  digitalWrite(cs,HIGH); spi->endTransaction();
  /*Serial.print("time:"); Serial.println(sampleTimeAxis[n]);
  for(int ch=0;ch<8;ch++){
    Serial.print(adcRaws[ch][n]); Serial.print("\t");
  }
  Serial.println();*/
}

void ADS1256::setAll(int sampleInterval,int memSize){
  this->sampleInterval=sampleInterval;
  this->memSize=memSize;
  for(int i=0;i<memSize;i++){
    sampleTimeAxis[i]=i*sampleInterval;
  }
}

void ADS1256::runRoutineBlocking(){
  int n=0; unsigned long startTimeMicros=micros();
  while(n<memSize){
    if(micros()-startTimeMicros>sampleTimeAxis[n]){
      adcRead(n); n++;
    }
  }
  send();
}

//"{\"chip2\":[[1,2,3],[4,5,6]]}"
void ADS1256::send(){
  String message=String("{\"")+chipId+"\":[";
  for(int ch=0;ch<8;ch++){
    message+="[";
    for(int n=0;n<memSize;n++){
      message+=String(adcRaws[ch][n]);
      if(n!=memSize-1) message+=","; else message+="]";
    }
    if(ch!=7) message+=",";
  }
  //Serial.println(message);
  ADS1256WantsToBroadcastTXT(message+"]}");
}
