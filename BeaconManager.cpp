#include "BeaconManager.h"

BLEDevicesListener::BLEDevicesListener(AdvertisedBeaconCallbacks* listener) {
  this->listener = listener;
}

void BLEDevicesListener::onResult(BLEAdvertisedDevice advertisedDevice) {
  if (advertisedDevice.haveManufacturerData()) {
    std::string manufacturerData = advertisedDevice.getManufacturerData();
    int length = manufacturerData.length();
    
    char* packet = BLEUtils::buildHexData(nullptr, (uint8_t*) manufacturerData.data(), length);
    listener->onResult(packet);
    free(packet);
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
