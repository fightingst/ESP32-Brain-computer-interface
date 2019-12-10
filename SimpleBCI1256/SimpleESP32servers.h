/*
  SimpleESP32servers.h 
  - Wrap up **WebServer** and **WebSocketsServer** codes for ESP32.
  Created by Tesla Cat (Ding Ruiqi), Sept 11, 2019.
  This code is private and commercial use is not allowed.
*/
#ifndef SimpleESP32servers_h
#define SimpleESP32servers_h

//////////////////// Begin Class Definition //////////////
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
//#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

void customHandleWebSocketsText(uint8_t *payload);

class SimpleESP32servers{
private:
    WebServer *webServer;
    WebSocketsServer *webSocketsServer;
    
    void handleFileUpload();
    bool handleFileRead(String myPath);
    void handleWebSocketsEvent(uint8_t num,
                               WStype_t type,
                               uint8_t * payload,
                               size_t length);
    void handleWebSocketsText(uint8_t * payload);

public:
    bool isConnected;
    
    SimpleESP32servers();
    void startWiFiAndServers(
            const char* WiFiID,
            const char* WiFiPassword);
    void runRoutine();
    void broadcastTXT(String text);
};
//////////////////// End Class Definition //////////////

#endif
