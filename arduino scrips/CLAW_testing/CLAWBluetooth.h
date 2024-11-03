#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class CLAWBluetooth
{
    private:
        
        BLEServer* pServer;
        BLECharacteristic* pCharacteristic;
        u_int32_t value;
        
    public:

        CLAWBluetooth();
        void begin();
        String getName();
        int getDevices();
        
        int deviceConnected = 0;
        String status = "some important message here";
        
        BLECharacteristic *pCharacteristicTransmit;
        BLECharacteristic *pCharacteristicRecive;
};

class CharacteristicChangeCallbacks: public BLECharacteristicCallbacks
{
    private:

        CLAWBluetooth* BT;

    public:

        void onWrite(BLECharacteristic *pCharacteristic);
        CharacteristicChangeCallbacks(CLAWBluetooth* _BT);
};


class MyServerCallbacks: public BLEServerCallbacks
{
    private: 
    
        CLAWBluetooth* BT;

    public:

        MyServerCallbacks(CLAWBluetooth* _BT);
        void onConnect(BLEServer* pServer);
        void onDisconnect(BLEServer* pServer);
};

