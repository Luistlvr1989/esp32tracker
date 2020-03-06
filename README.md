# ESP32 Beacons detection with MQTT transmission

This code shows how to capture BLE iBeacon packages and transmit them over MQTT. WiFi configuration is also included in the WiFiManager.

Currently only iBeacon is supported.

## Usage

Just create a Config.h file similar to Config.h.example and add the required configuration for your WiFi network and MQTT broker. 

Use the connectEnterprise method from the WiFiManager to connect to WPA/WPA2 Enterprise networks, otherwise use the connect method.

```cpp
  wifiManager.connect("ssid", "password");
  wifiManager.connectEnterprise("ssid", "identity", "password");
```

## License
[Apache 2.0](https://choosealicense.com/licenses/apache-2.0/)

```
   Copyright (C) 2020 Luis Talavera Ríos

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
```

### Contributing to Android MVVM Architecture
Just make pull request!