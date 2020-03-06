# ESP32 Beacons detection with MQTT transmission

This code shows how to capture BLE iBeacon packages and transmit them over MQTT. WiFi configuration is also included in the WiFiManager.

Currently only iBeacon is supported.

## Usage

Just create a Config.h file similar to Config.h.example and add the required configuration for your WiFi network and MQTT broker. 

Use the connectEnterprise method from the WiFiManager to connect to WPA/WPA2 Enterprise networks, otherwise use the connect method.

```cpp
  wifiManager.connect(wifiSsid, wifiPassword);
  wifiManager.connectEnterprise(wifiSsid, wifiIdentity, wifiPassword);
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[Apache 2.0](https://choosealicense.com/licenses/apache-2.0/)