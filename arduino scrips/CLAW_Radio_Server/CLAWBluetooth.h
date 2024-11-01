

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class CLAWBluetooth
{
    private:
        
    
    public:

        CLAWBluetooth();
        String serverName();

        BLEServer* pServer;
        BLECharacteristic* pCharacteristic;
        u_int32_t value;
        int deviceConnected;

        BLECharacteristic *pCharacteristicTransmit;
        BLECharacteristic *pCharacteristicRecive;

        //void CharacteristicChangeCallbacks::onWrite(BLECharacteristic *pCharacteristic);

};

class CharacteristicChangeCallbacks: public BLECharacteristicCallbacks
{
    public:

        void onWrite(BLECharacteristic *pCharacteristic);

};


class MyServerCallbacks: public BLEServerCallbacks
{
    public:

        void onConnect(BLEServer* pServer);
        void onDisconnect(BLEServer* pServer);
};

