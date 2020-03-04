#include "WiFiManager.h"

void WiFiManager::begin() {
  WiFi.disconnect(true);  
  WiFi.mode(WIFI_STA);
}

void WiFiManager::scanNetworks() {
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
  }
}

String WiFiManager::translateEncryptionType(wifi_auth_mode_t encryptionType) {
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

void WiFiManager::connect(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  waitForConnection();
}

void WiFiManager::connectEnterprise(const char* ssid, const char* identity, const char* password) {
  this->ssid = (char*) ssid;
  
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)identity, strlen(identity)); 
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)identity, strlen(identity)); 
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password)); 
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); 
  esp_wifi_sta_wpa2_ent_enable(&config); 
  
  WiFi.begin(ssid); 
  waitForConnection();
}

void WiFiManager::waitForConnection() {
  Serial.print("Establishing connection to WiFi..");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    
    counter++;
    if (counter >= TIMEOUT) {
      Serial.println("");
      ESP.restart();
    }
  }

  counter = 0;
  Serial.println("");
  Serial.println("Connected to network");
  Serial.println("IP address set: ");
  Serial.println(WiFi.localIP());
}

void WiFiManager::loop() {
  if (WiFi.status() != WL_CONNECTED) { 
    WiFi.begin(ssid);      
    waitForConnection();
  }
}

WiFiManager wifiManager;
