#include "SimpleESP32servers.h"
#include "SimpleAnalogRead.h"
#include <ArduinoJson.h>
//==============================================
// Global Variables
//==============================================

SimpleESP32servers simpleESP32servers;
SimpleAnalogRead simpleAnalogRead;
StaticJsonDocument<400> doc;

//==============================================
// Functions
//==============================================
void customHandleWebSocketsText(uint8_t * payload) {
  String message = String( (char *)payload );
  
  if( message.startsWith("guiData:")){
    deserializeJson(doc,(char *)(payload+strlen("guiData:")));
    int sampleInterval=doc["sampleInterval"];
    int tolerance=doc["tolerance"];
    int pin=doc["pin"];
    int memSize=doc["memSize"];
    simpleAnalogRead.setAll(sampleInterval, tolerance, pin, memSize);
  }
}

void analogReadWantsToBroadcastTXT(String message){
  simpleESP32servers.broadcastTXT(message);
}

void setup(){
  simpleESP32servers.startWiFiAndServers("Tesla Coil Sing!","12345678");
}

void loop(){
  simpleESP32servers.runRoutine();
  simpleAnalogRead.runRoutine();
}
