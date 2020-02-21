#include "BeaconManager.h"

BLEDevicesListener::BLEDevicesListener(AdvertisedBeaconCallbacks* listener) {
  this->listener = listener;
}

void BLEDevicesListener::onResult(BLEAdvertisedDevice advertisedDevice) {
  std::string data = advertisedDevice.getManufacturerData();

  if (advertisedDevice.haveManufacturerData()) {
    listener->onResult(advertisedDevice);
  }
}

void BeaconManager::begin(AdvertisedBeaconCallbacks* listener) {
  BLEDevice::init("");
  bleScan = BLEDevice::getScan(); 
  bleScan->setAdvertisedDeviceCallbacks(new BLEDevicesListener(listener));
  bleScan->setActiveScan(true); 
  bleScan->setInterval(INTERVAL);
  bleScan->setWindow(WINDOW);  
}

void BeaconManager::scan(uint32_t duration) {
  bleScan->start(duration, false);
  bleScan->clearResults(); 
}

BeaconManager beaconManager;
