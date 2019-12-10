#include "ADS1256.h"

ADS1256::ADS1256(
  int CLK,int CS,int READY, int SYNC, int RESET,
  int spiSpeed){

  clk=CLK;cs=CS;ready=READY;sync=SYNC;reset=RESET;this->spiSpeed=spiSpeed;
  ledcSetup(0,8000000,1);//channel,frequency,resolution
  ledcAttachPin(clk,0);//pin,channel
  ledcWrite(0,1); delay(1); //channel,dutyCycle
  pinMode(cs,OUTPUT); digitalWrite(cs,LOW);
  pinMode(ready,INPUT);
  pinMode(sync,OUTPUT); digitalWrite(sync,HIGH);
  pinMode(reset,OUTPUT); digitalWrite(reset,LOW);
  delay(1); digitalWrite(reset,HIGH);
  spi=new SPIClass(VSPI);
  spi->begin();
  while(digitalRead(ready)){/*wait til LOW*/}
  // SPI_MODE1 vs SPI_MODE0 ???????????????????
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

void ADS1256::read(){
  spi->beginTransaction(SPISettings(spiSpeed,MSBFIRST,SPI_MODE1));
  digitalWrite(cs,LOW); delayMicroseconds(2); int i;
  for(i=0;i<=7;i++){
    while(digitalRead(ready)){/*wait til LOW*/}
    spi->transfer(0x50|0x01);
    spi->transfer(0x00); spi->transfer(channels[i]);
    delayMicroseconds(2);
    //SYNC command 1111 1100
    spi->transfer(0xFC); delayMicroseconds(2);
    spi->transfer(0x00); delayMicroseconds(250);
    // Read Data 01h
    spi->transfer(0x01); delayMicroseconds(5);
    adcRaws[i]=spi->transfer(0); adcRaws[i]<<8;
    adcRaws[i]=spi->transfer(0); adcRaws[i]<<8;
    adcRaws[i]=spi->transfer(0); delayMicroseconds(2);
  }
  digitalWrite(cs,HIGH); spi->endTransaction();
  //2's complement
  for(i=0;i<=7;i++){
    if(adcRaws[i]>0x7fffff) adcRaws[i]-=0x1000000;
    adcVals[i]=adcRaws[i];
  }
}
