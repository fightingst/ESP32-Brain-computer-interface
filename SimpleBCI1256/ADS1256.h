#ifndef ADS1256_h
#define ADS1256_h

#include <Arduino.h>
#include <SPI.h>

void ADS1256WantsToBroadcastTXT(String message);

class ADS1256{
private:
  int sampleInterval,memSize;
  unsigned long sampleTimeAxis[2000];

  uint8_t clk,cs,dtReady,sync,reset; //pins
  uint32_t spiSpeed; String chipId;
  SPIClass* spi;
  long adcRaws[8][2000];
  byte channels[8]={0x08,0x18,0x28,0x38,0x48,0x58,0x68,0x78};
  void adcRead(int n);
  void send(); void sendJson();
public:
  ADS1256(
    int CLK,int CS,int READY, int SYNC, int RESET,
    int spiSpeed, String chipId);
  void setAll(
    int sampleInterval, int memSize);
  void runRoutineBlocking();
};

#endif
