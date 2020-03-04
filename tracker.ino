#include "WiFiManager.h"
#include "BeaconManager.h"
#include "MQTTManager.h"
#include "Config.h"

const char* wifiSsid = WIFI_SSID;
//const char* wifiIdentity = WIFI_IDENTITY;
const char* wifiPassword = WIFI_PASSWORD;

const int durationInSeconds = 5;

const char* mqttServer = MQTT_SERVER;
const int mqttPort = MQTT_PORT;
const char* mqttUser = MQTT_USER;
const char* mqttPassword = MQTT_PASSWORD;
const char* mqttPublishChannel = MQTT_PUBLISH_CH;

class BeaconsListener: public AdvertisedBeaconCallbacks {
    void onResult(char* packet) {
      Serial.printf("Advertised Package: %s \n", packet);
      mqttManager.publish(mqttPublishChannel, packet);
    }
};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  wifiManager.begin();
  //wifiManager.connectEnterprise(wifiSsid, wifiIdentity, wifiPassword);
  wifiManager.connect(wifiSsid, wifiPassword);

  mqttManager.begin(mqttServer, mqttPort);
  mqttManager.connect(mqttUser, mqttPassword);

  beaconManager.begin(new BeaconsListener());
}

void loop() {
  wifiManager.loop();
  mqttManager.loop();

  beaconManager.scan(durationInSeconds);
  delay(2000);
}
