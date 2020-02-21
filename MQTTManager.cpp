#include "MQTTManager.h"

MQTTManager::MQTTManager() {
  client = new PubSubClient(wifiClient);
}

void MQTTManager::begin(const char* server, int port) {
  client->setServer(server, port);
}

void MQTTManager::connect(const char* user, const char* password) {
  this->user = (char*) user;
  this->password = (char*) password;
  
  while (!client->connected()) {
    Serial.print("Establishing MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    Serial.println("");
    if (client->connect(clientId.c_str(), user, password)) {
      Serial.println("Connected to server");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client->state());
      Serial.println(" try again in 5 seconds");
      delay(RETRY * 1000);
    }
  }
}

void MQTTManager::publish(const char* topic, const char* data) {
  if (!client->connected()) {
    connect(user, password);
  }
  
  client->publish(topic, data);
}

void MQTTManager::loop() {
  client->loop();
}

MQTTManager::~MQTTManager() {
  delete client;
}


MQTTManager mqttManager;
