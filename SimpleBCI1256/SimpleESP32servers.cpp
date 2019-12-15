/*
  SimpleESP32servers.cpp
  - Wrap up **WebServer** and **WebSocketsServer** codes for ESP32.
  Created by Tesla Cat (Ding Ruiqi), Sept 11, 2019.
  This code is private and commercial use is not allowed.
*/

#include "SimpleESP32servers.h"

//////////////////// Begin Methods Definition //////////////

SimpleESP32servers::SimpleESP32servers() {
    isConnected=false;
}

void SimpleESP32servers::startWiFiAndServers(
        const char *WiFiID,
        const char *WiFiPassword) {
    Serial.begin(115200); delay(10);

    SPIFFS.begin();

    int numberOfNetworks = WiFi.scanNetworks();
    for(int i=0; i<numberOfNetworks;i++) Serial.println(WiFi.SSID(i));
    WiFi.softAP("ESP32","12345678"); 
    WiFi.begin(WiFiID,WiFiPassword); 
    while(1){
      if(WiFi.softAPgetStationNum()) {Serial.println("AP");break;}
      if(WiFi.status()==WL_CONNECTED) {Serial.println("STA");break;}
      Serial.println(WiFi.status());
      delay(500);
    }
    Serial.println(WiFi.localIP());
    
    webServer = new WebServer(80);
    webServer->on("/FileUpload.html",
                  HTTP_POST,
                  [this](){ webServer->send(200,"text/plain","");},
                  [this](){ handleFileUpload();});
    webServer->onNotFound(
            [this]() {
                if (!handleFileRead(webServer->uri()))
                    webServer->send(404,"text/plain","404");
            });
    webServer->begin();

    webSocketsServer = new WebSocketsServer(81);
    webSocketsServer->begin();
    webSocketsServer->onEvent(
            [this](uint8_t num, WStype_t type, uint8_t *payload, size_t length){
                handleWebSocketsEvent(num,type,payload,length);
            });

    delay(1000);
}

void SimpleESP32servers::runRoutine() {
    webServer->handleClient();
    webSocketsServer->loop();
}

void SimpleESP32servers::handleFileUpload() {
    //Serial.println("handleFileUpload");
    File uploadFile;
    HTTPUpload& upload = webServer->upload();
    String myPath;
    if(upload.status == UPLOAD_FILE_START){
        myPath = upload.filename;
        if(!myPath.startsWith("/")) myPath="/"+myPath;
        if(!myPath.endsWith(".gz") && SPIFFS.exists(myPath+".gz"))
            SPIFFS.remove(myPath+".gz");
        uploadFile = SPIFFS.open(myPath,"w");
    }
    else if(upload.status == UPLOAD_FILE_WRITE){
        if(uploadFile) uploadFile.write(upload.buf, upload.currentSize);
    }
    else if(upload.status == UPLOAD_FILE_END){
        if(uploadFile) uploadFile.close();
        else webServer->send(500,"text/plain","500: Can't Write File");
    }
}

bool SimpleESP32servers::handleFileRead(String myPath) {
    //Serial.println("handleFileRead: "+myPath);
    if(myPath.endsWith("/")) myPath+="index.html";
    if(SPIFFS.exists(myPath)){
        File file = SPIFFS.open(myPath,"r");
        String type;
        if(myPath.endsWith(".html"))     type = "text/html";
        else if(myPath.endsWith(".css")) type = "text/css";
        else if(myPath.endsWith(".js"))  type = "application/javascript";
        else if(myPath.endsWith(".gz"))  type = "application/x-gzip";
        else                             type = "text/plain";
        webServer->streamFile(file, type );
        file.close();
        return true;
    }
    return false;
}

void SimpleESP32servers::handleWebSocketsEvent(uint8_t num,
                                             WStype_t type,
                                             uint8_t *payload,
                                             size_t length) {
    //Serial.println("handleWebSocketsEvent");
    switch (type){
        case WStype_DISCONNECTED:{
           isConnected=false;
        }break;
        case WStype_CONNECTED:{
            isConnected=true;
            IPAddress ip = webSocketsServer->remoteIP(num);
            //Serial.printf("[%u] Connected from %d.%d.%d.%d url:%s\n",
            //              num,ip[0],ip[1],ip[2],ip[3],payload);
        }break;
        case WStype_TEXT:
            customHandleWebSocketsText(payload);
            break;
    }
}

void SimpleESP32servers::handleWebSocketsText(uint8_t *payload) {
    String message = String( (char *)payload );
    //Serial.println("handleWebSocketsText: "+message);
}

void SimpleESP32servers::broadcastTXT(String text){
    webSocketsServer->broadcastTXT(text);
}

//////////////////// End Methods Definition //////////////
