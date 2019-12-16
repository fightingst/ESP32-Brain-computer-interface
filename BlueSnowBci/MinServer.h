#ifndef MinServer_h
#define MinServer_h

#include <WiFi.h>
#include <WebSocketsServer.h>

void onmessage(uint8_t* msg);

class MinServer{
private:
  WebSocketsServer* webSocketsServer;
public:
  bool wsConnected;
  MinServer();
  void runRoutine();
  void connectWifi(char* id,char* password);
  void broadcastTXT(String msg);
};

#endif
