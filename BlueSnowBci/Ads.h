#ifndef Ads_h
#define Ads_h

#include<Arduino.h>
#include<SPI.h>

void AdsWantsToBroadcastTXT(String message);

class Ads{
private:
  uint8_t cs,dtReady; uint32_t spiSpeed; String chipId;
  SPIClass* spi;
  int sampleFreq,memSize;
  unsigned long sampleTimeAxis[2000];
  long adcRaws[8][2000];
  byte channels[8]={0x08,0x18,0x28,0x38,0x48,0x58,0x68,0x78};
  void adsRead(int n);
public:
  Ads();
  void setAll(int sampleFreq,int memSize);
  void fillMemAndSend();
  void init(int clk,int cs,int dtReady,int sync,
    int reset,int spiSpeed,String chipId);
};

#endif
