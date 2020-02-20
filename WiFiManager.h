#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "esp_wpa2.h"

class WiFiManager {
private:
  String translateEncryptionType(wifi_auth_mode_t);

public:
  void scanNetworks();
  
  void begin();
  
  bool connect();
};

extern WiFiManager wifiManager;

#endif
