#include "BeaconManager.h"

BLEDevicesListener::BLEDevicesListener(AdvertisedBeaconCallbacks* listener) {
  this->listener = listener;
}

void BLEDevicesListener::onResult(BLEAdvertisedDevice advertisedDevice) {
  if (advertisedDevice.haveManufacturerData()) {
    std::string manufacturerData = advertisedDevice.getManufacturerData();
    int length = manufacturerData.length();

    if (BeaconManager::isSupportedBeacon(manufacturerData, length)) {
      char* packet = BLEUtils::buildHexData(nullptr, (uint8_t*) manufacturerData.data(), length);
      listener->onResult(packet);
      free(packet);
    }
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

bool BeaconManager::isSupportedBeacon(std::string manufacturerData, int length) {
  uint8_t data[100];
  manufacturerData.copy((char*) data, length, 0);

  if (isIBeacon(data)) {
    return true;
  }
  
  return false;
}

bool BeaconManager::isIBeacon(uint8_t* data) {
  return data[0] == 0x4C && data[1] == 0x00 && data[2] == 0x02;
}

BeaconManager beaconManager;
