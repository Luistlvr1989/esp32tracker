#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "esp_wpa2.h"
#include <Wire.h>

#define TIMEOUT 45

class WiFiManager {
private:
  char* ssid;
  int counter = 0;
  
  String translateEncryptionType(wifi_auth_mode_t);

  void waitForConnection();

public:
  void scanNetworks();
  
  void begin();
  
  void connect(const char*, const char*);

  void connectEnterprise(const char*, const char*, const char*);

  void loop();
};

extern WiFiManager wifiManager;

#endif
