#ifndef BEACON_MANAGER_H
#define BEACON_MANAGER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define INTERVAL 100
#define WINDOW 99

struct AdvertisedBeaconCallbacks {
  virtual void onResult(BLEAdvertisedDevice advertisedDevice);
};

class BeaconManager {
private:
  BLEScan* bleScan;
  
public: 
  void begin(AdvertisedBeaconCallbacks*);

  void scan(uint32_t);

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
