#ifndef BEACON_MANAGER_H
#define BEACON_MANAGER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <esp_log.h>

#define INTERVAL 100
#define WINDOW 99

struct AdvertisedBeaconCallbacks {
  virtual void onResult(char*);
};

class BeaconManager {
private:
  BLEScan* bleScan;
  
public: 
  void begin(AdvertisedBeaconCallbacks*);

  void scan(uint32_t);

  static bool isSupportedBeacon(std::string, int);

  static bool isIBeacon(uint8_t*);
  
  friend class BLEDevicesListener;
};

class BLEDevicesListener: public BLEAdvertisedDeviceCallbacks {
private:
  AdvertisedBeaconCallbacks* listener;

public:
  BLEDevicesListener(AdvertisedBeaconCallbacks*);
  
  void onResult(BLEAdvertisedDevice advertisedDevice);
};

extern BeaconManager beaconManager;

#endif
