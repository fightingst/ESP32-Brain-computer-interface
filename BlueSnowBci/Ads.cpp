#include "Ads.h"

Ads::Ads(){}

void Ads::setAll(int sampleFreq,int memSize){
  this->sampleFreq=sampleFreq; this->memSize=memSize;
  for(int i=0;i<memSize;i++) sampleTimeAxis[i]=i*1e6/sampleFreq; 
}

void Ads::fillMemAndSend(){
  int n=0; unsigned long start=micros();
  while(n<memSize){
    if(micros()-start>sampleTimeAxis[n]) adsRead(n++);
  }
  String message=String("{\"")+chipId+"\":[";
  for(int ch=0;ch<8;ch++){ message+="[";
    for(n=0;n<memSize;n++){
      message+=String(adcRaws[ch][n]); 
      if(n!=memSize-1) message+=","; else message+="]";
    }
    if(ch!=7) message+=","; else message+="]"; 
  } 
  Serial.println(millis());
  AdsWantsToBroadcastTXT(message+"}");
}

void Ads::init(int clk,int cs,int dtReady,int sync,
int reset,int spiSpeed,String chipId){
  setAll(200,100);
  this->cs=cs; this->dtReady=dtReady;
  this->spiSpeed=spiSpeed; this->chipId=chipId;
  ledcSetup(0,8000000,1); ledcAttachPin(clk,0); ledcWrite(0,1);
  pinMode(cs,OUTPUT); pinMode(dtReady,INPUT);
  pinMode(sync,OUTPUT); digitalWrite(sync,HIGH);
  pinMode(reset,OUTPUT); digitalWrite(reset,LOW);
  delay(1); digitalWrite(reset,HIGH); delay(500);
  spi=new SPIClass(VSPI); spi->begin(); delay(500);
  while(digitalRead(dtReady)){}

  spi->beginTransaction(SPISettings(spiSpeed,MSBFIRST,SPI_MODE1));
  digitalWrite(cs,LOW); delayMicroseconds(100);
  spi->transfer(0xFE); delay(5);
  const byte regNdata[6]={0x00,0x01,0x02,0x00,0x03,0xF0};
  for(int i=0;i<3;i++){
    spi->transfer(0x50|regNdata[i]); spi->transfer(0x00);
    spi->transfer(regNdata[i+1]); delayMicroseconds(100);
  }
  spi->transfer(0xF0); delay(400);
  digitalWrite(cs,HIGH); spi->endTransaction();
}

void Ads::adsRead(int n){
  spi->beginTransaction(SPISettings(spiSpeed,MSBFIRST,SPI_MODE1));
  digitalWrite(cs,LOW); delayMicroseconds(2);
  for(int ch=0;ch<8;ch++){
    while(digitalRead(dtReady)){}
    spi->transfer(0x50|0x01); spi->transfer(0x00);
    spi->transfer(channels[ch]); delayMicroseconds(2);
    spi->transfer(0xFC); delayMicroseconds(2);
    spi->transfer(0x00); delayMicroseconds(250);
    spi->transfer(0x01); delayMicroseconds(5);
    long x;
    x=spi->transfer(0);  x<<=8;
    x|=spi->transfer(0); x<<=8;
    x|=spi->transfer(0); delayMicroseconds(2);
    if(x>0x7fffff) x-=16777216; //2's complement
    adcRaws[ch][n]=x;
  }
  digitalWrite(cs,HIGH); spi->endTransaction();
}
