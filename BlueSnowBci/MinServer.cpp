
#include "MinServer.h"

MinServer::MinServer(){}

void MinServer::runRoutine(){
  webSocketsServer->loop();
}

void MinServer::connectWifi(char* id,char* password){
  Serial.begin(115200); wsConnected=false;
  /*WiFi.begin(id, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); int n = WiFi.scanNetworks();
    if (n == 0) Serial.println("no networks found");
    else for (int i = 0; i < n; ++i) {
        Serial.print(i); Serial.print(": "); Serial.print(WiFi.SSID(i)); 
        Serial.print("\t");  Serial.println(WiFi.RSSI(i));  delay(10);
    }  
  }*/
  WiFi.softAP("FUCK","YOURMOTHER");
  Serial.print("\n IP address: "); Serial.println(WiFi.softAPIP());
  
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
