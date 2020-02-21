#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <PubSubClient.h>
#include <WiFi.h>

#define RETRY 5

class MQTTManager {
private:
  WiFiClient wifiClient;
  
  PubSubClient* client;

  char* user;

  char* password;

public:
  MQTTManager();

  void begin(const char*, int);

  void connect(const char*, const char*);

  void publish(const char*, const char*);

  void loop();

  ~MQTTManager();
};

extern MQTTManager mqttManager;

#endif
