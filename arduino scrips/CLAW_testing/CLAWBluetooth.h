

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
        String serverName();
        int getDevices();
        
        int deviceConnected = 0;
        
        BLECharacteristic *pCharacteristicTransmit;
        BLECharacteristic *pCharacteristicRecive;
        //void CharacteristicChangeCallbacks::onWrite(BLECharacteristic *pCharacteristic);

};

class CharacteristicChangeCallbacks: public BLECharacteristicCallbacks
{
    public:

        void onWrite(BLECharacteristic *pCharacteristic);
        CharacteristicChangeCallbacks(CLAWBluetooth* _BT);

    private:

        CLAWBluetooth* BT;


};


class MyServerCallbacks: public BLEServerCallbacks
{
    public:

        MyServerCallbacks(CLAWBluetooth* _BT);
        void onConnect(BLEServer* pServer);
        void onDisconnect(BLEServer* pServer);

    private: 
    
        CLAWBluetooth* BT;
};

