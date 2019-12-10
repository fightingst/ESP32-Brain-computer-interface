#include "SimpleESP32servers.h"
//#include "SimpleAnalogRead.h"
#include "ADS1256.h"
#include <ArduinoJson.h>
//==============================================
// Global Variables
//==============================================

SimpleESP32servers simpleESP32servers;
//SimpleAnalogRead simpleAnalogRead;
//ADS1256(int CLK,int CS,int READY, int SYNC, int RESET,int spiSpeed);
ADS1256 aDS1256(17,15,2,4,16,2000000);
StaticJsonDocument<400> doc;

//==============================================
// Functions
//==============================================
void customHandleWebSocketsText(uint8_t * payload) {
  String message = String( (char *)payload );

  if ( message.startsWith("guiData:")) {
    deserializeJson(doc, (char *)(payload + strlen("guiData:")));
    int sampleInterval = doc["sampleInterval"];
    int pin = doc["pin"];
    int memSize = doc["memSize"];
    //simpleAnalogRead.setAll(sampleInterval, pin, memSize);
  }
}

void analogReadWantsToBroadcastTXT(String message) {
  simpleESP32servers.broadcastTXT(message);
}

void setup() {
  //simpleESP32servers.startWiFiAndServers("Tesla Coil Sing!", "12345678");
  Serial.begin(115200);
}

void loop() {
  //simpleESP32servers.runRoutine();
  //simpleAnalogRead.runRoutineBlocking();
  aDS1256.read();
  for(int i=0;i<=7;i++){
    Serial.print(aDS1256.adcVals[i]); Serial.print("\t");  
  }
  Serial.println(); delay(500);
}
