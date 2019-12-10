#ifndef ADS1256_h
#define ADS1256_h

#include <Arduino.h>
#include <SPI.h>

class ADS1256{
private:
  uint8_t clk,cs,ready,sync,reset; //pins
  uint32_t spiSpeed;
  SPIClass* spi;
  unsigned long adcRaws[8]={0,0,0,0,0,0,0,0};
  byte channels[8]={0x08,0x18,0x28,0x38,0x48,0x58,0x68,0x78};
public:
  ADS1256(
    int CLK,int CS,int READY, int SYNC, int RESET,
    int spiSpeed);
  unsigned long adcVals[8];
  void read();
};

#endif
