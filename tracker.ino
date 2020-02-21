#include "WiFiManager.h"
#include "BeaconManager.h"

/*const char* ssid = "Belatrix Globant Division";
const char* identity = "ltalavera";
const char* password = "4I6goj8X!!";*/

const char* ssid = "TALAVERA";
const char* password = "29252217";

const int durationInSeconds = 5;

class BeaconsListener: public AdvertisedBeaconCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  wifiManager.begin();
  //wifiManager.connectEnterprise(ssid, identity, password);
  wifiManager.connect(ssid, password);

  beaconManager.begin(new BeaconsListener());
}

void loop() {
  beaconManager.scan(durationInSeconds);
  delay(2000);
}





/*#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "BLEBeacon.h"

#define SCAN_TIME_IN_SECONDS 5
#define DELAY_SCAN_IN_SECONDS 10

uint16_t beconUUID = 0x4c00;

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
      
      if (advertisedDevice.haveManufacturerData()) {
        char *pHex = BLEUtils::buildHexData(nullptr, (uint8_t*)advertisedDevice.getManufacturerData().data(), advertisedDevice.getManufacturerData().length());
        Serial.println(pHex);
        free(pHex);
      }
    }
};
*/
/*
#include <WiFi.h>
#include <PubSubClient.h>

const char* SSID = "TALAVERA";
const char* PASSWORD = "29252217";

const char* mqtt_server = "hornet.rmq.cloudamqp.com";
#define mqtt_port 1883
#define MQTT_USER "znuhuljz:znuhuljz"
#define MQTT_PASSWORD "iA1pLdUFq6MD_gOmqLQWDgrA4iUOshUx"
#define MQTT_SERIAL_PUBLISH_CH "/icircuit/ESP32/serialdata/tx"
#define MQTT_SERIAL_RECEIVER_CH "/icircuit/ESP32/serialdata/rx"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
 
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      client.publish("/icircuit/presence/ESP32/", "hello world");
      client.subscribe(MQTT_SERIAL_RECEIVER_CH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    Serial.write(payload, length);
    Serial.println();
}

void setup() {
  Serial.begin(9600);

  scanNetworks();
  connectToNetwork();

  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); 
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  
}

void publishSerialData(char *serialData){
  if (!client.connected()) {
    reconnect();
  }
  client.publish(MQTT_SERIAL_PUBLISH_CH, serialData);
}

void loop() {
  client.loop();
  
  if (Serial.available() > 0) {
     char mun[501];
     memset(mun,0, 501);
     Serial.readBytesUntil( '\n',mun,500);
     publishSerialData(mun);
   }
  
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME_IN_SECONDS, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   
  delay(DELAY_SCAN_IN_SECONDS * 1000);
}*/
