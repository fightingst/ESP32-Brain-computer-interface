#include "SimpleESP32servers.h"
#include <ArduinoJson.h>
//==============================================
// Global Variables
//==============================================

SimpleESP32servers simpleESP32servers;
StaticJsonDocument<400> doc;

//==============================================
// Functions
//==============================================
void customHandleWebSocketsText(uint8_t * payload) {
  String message = String( (char *)payload );
  //Serial.println(message);

  if(message.startsWith("analogRead:")){
    deserializeJson(doc,(char *)(payload+strlen("analogRead:")));
    int pin=doc["pin"];
    //Serial.println(pin);
    int value=analogRead(pin);
    String msg = String("analogRead:{")
      +"\"pin\":"+String(pin)
      +",\"value\":"+String(value)+"}";
    simpleESP32servers.broadcastTXT(msg);
    //Serial.println(msg);
  }

  else if( message.startsWith("guiData:")){
    deserializeJson(doc,(char *)(payload+strlen("guiData:")));
  }
}

void setup(){
  simpleESP32servers.startWiFiAndServers("Tesla Coil Sing!","12345678");
}

void loop(){
  simpleESP32servers.runRoutine();
}
