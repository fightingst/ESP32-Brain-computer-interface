
#include "MinServer.h"

MinServer::MinServer(){}

void MinServer::runRoutine(){
  webSocketsServer->loop();
}

void MinServer::connectWifi(char* id,char* password){
  Serial.begin(115200); wsConnected=false;
  WiFi.softAP("fuck","12345678");
  WiFi.begin(id,password);
  while(!(WiFi.softAPgetStationNum()||WiFi.status()==WL_CONNECTED)){}
  Serial.println(WiFi.localIP());
  webSocketsServer=new WebSocketsServer(81);
  webSocketsServer->begin();
  webSocketsServer->onEvent([this]
    (uint8_t num,WStype_t type,uint8_t* msg,size_t length){
      switch(type){
        case WStype_DISCONNECTED:{wsConnected=false;
          Serial.println("DISCONNECTED");} break;
        case WStype_CONNECTED:{wsConnected=true;
          Serial.println("CONNECTED");} break;
        case WStype_TEXT:{onmessage(msg);} break;
      }
    }
  );
}

void MinServer::broadcastTXT(String msg){
  webSocketsServer->broadcastTXT(msg);
}
