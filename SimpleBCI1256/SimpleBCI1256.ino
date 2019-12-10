#include "SimpleESP32servers.h"
#include "ADS1256.h"
#include <ArduinoJson.h>
//==============================================
// Global Variables
//==============================================

SimpleESP32servers simpleESP32servers;
//ADS1256(int CLK,int CS,int READY, int SYNC, int RESET,int spiSpeed, String chipId);
ADS1256 aDS1256(17,15,2,4,16,2000000, "chip2");
StaticJsonDocument<400> doc;

//==============================================
// Functions
//==============================================
void customHandleWebSocketsText(uint8_t * payload) {
  String message = String( (char *)payload );

  if ( message.startsWith("guiData:")) {
    deserializeJson(doc, (char *)(payload + strlen("guiData:")));
    int sampleInterval = doc["sampleInterval"];
    int memSize = doc["memSize"];
    aDS1256.setAll(sampleInterval, memSize);
  }
}

void ADS1256WantsToBroadcastTXT(String message) {
  simpleESP32servers.broadcastTXT(message);
  //Serial.println(message);
}

void setup() {
  simpleESP32servers.startWiFiAndServers("Tesla Coil Sing!", "12345678");
  Serial.begin(115200); 
}

void loop() {
  simpleESP32servers.runRoutine();
  aDS1256.runRoutineBlocking();
}
