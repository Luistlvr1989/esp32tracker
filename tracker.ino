#include "WiFiManager.h"
#include "BeaconManager.h"
#include "MQTTManager.h"

/*const char* WIFI_SSID = "Belatrix Globant Division";
const char* WIFI_IDENTITY = "ltalavera";
const char* WIFI_PASSWORD = "4I6goj8X!!";*/

const char* WIFI_SSID = "TALAVERA";
const char* WIFI_PASSWORD = "29252217";

const int durationInSeconds = 5;

const char* MQTT_SERVER = "hornet.rmq.cloudamqp.com";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "znuhuljz:znuhuljz";
const char* MQTT_PASSWORD = "iA1pLdUFq6MD_gOmqLQWDgrA4iUOshUx";
const char* MQTT_PUBLISH_CH = "/tracker/beacon/packet";

class BeaconsListener: public AdvertisedBeaconCallbacks {
    void onResult(char* packet) {
      Serial.printf("Advertised Package: %s \n", packet);
      mqttManager.publish(MQTT_PUBLISH_CH, packet);
    }
};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  wifiManager.begin();
  //wifiManager.connectEnterprise(WIFI_SSID, WIFI_IDENTITY, WIFI_PASSWORD);
  wifiManager.connect(WIFI_SSID, WIFI_PASSWORD);

  mqttManager.begin(MQTT_SERVER, MQTT_PORT);
  mqttManager.connect(MQTT_USER, MQTT_PASSWORD);

  beaconManager.begin(new BeaconsListener());
}

void loop() {
  mqttManager.loop();
  
  beaconManager.scan(durationInSeconds);
  delay(2000);
}
