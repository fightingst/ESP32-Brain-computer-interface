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
  minServer.connectWifi("网络存在风险","940055940505QWE");
  ads.init(17,15,2,4,16,2000000,"chip2");
  ArduinoOTA.begin();
}

void loop(){
  minServer.runRoutine();
  if(minServer.wsConnected) ads.fillMemAndSend();
  ArduinoOTA.handle();
}
