#include <ArduinoOTA.h>
#include "MinServer.h"
#include "Ads.h"
#include <ArduinoJson.h>

MinServer minServer; Ads ads;
StaticJsonDocument<400> doc;

void onmessage(uint8_t* msg){
  String message=String((char*)msg);
  if(message.startsWith("guiData:")){
    deserializeJson(doc,(char*)(msg+strlen("guiData:")));
    int sampleFreq = doc["sampleFreq"];
    int memSize = doc["memSize"];
    ads.setAll(sampleFreq,memSize);
  }
}

void AdsWantsToBroadcastTXT(String message){
  minServer.broadcastTXT(message);
}

void setup(){
  Serial.begin(115200);
  ads.init(33,25,26,27,32,2000000,"1");
  minServer.connectWifi("SHAMELESS","00000000");
  //  void init(int clk,int cs,int dtReady,int sync,
  //  int reset,int spiSpeed,String chipId);
  ArduinoOTA.begin();
}

void loop(){
  Serial.println(millis()); delay(500);
  minServer.runRoutine();
  if(minServer.wsConnected) ads.fillMemAndSend();
  ArduinoOTA.handle();
}
