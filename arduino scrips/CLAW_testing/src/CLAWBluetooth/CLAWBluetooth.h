#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// remember to put all global variables and funtions in its .h file !

class CLAWBluetooth
{
    private:
        
        BLEServer* pServer;
        String setName();
        
    public:

        CLAWBluetooth();
        void begin();
        
        String getName();
        void setStatus(String newStatus);
        String getStatus();
        int getDevices();
        String getData();
        
        int deviceConnected = 0;
        String deviceName;
        String status = "[Bluetooth status]"; // placeholder status messege
        
        // object pointers are defined with an asterisk (*) by [type] *[name]
        // to access variables or call functions of object pointers, you need to use a pointer
        // [class]->[function/variable] as opposed to [class].[function/variable]

        BLECharacteristic *pCharacteristicTransmit;
        BLECharacteristic *pCharacteristicRecive;
};

class CharacteristicChangeCallbacks: public BLECharacteristicCallbacks
{
    private:

        // refrence to CLAWBT so it can manipulate variables 
        CLAWBluetooth* BT; 

    public:

        // pass CLAWBT as a parameter on contruction so it can access CLAWBT variables
        CharacteristicChangeCallbacks(CLAWBluetooth* _BT); 

        void onWrite(BLECharacteristic *pCharacteristic); 
};


class MyServerCallbacks: public BLEServerCallbacks
{
    private: 
    
        // refrence to CLAWBT so it can manipulate variables 
        CLAWBluetooth* BT;

    public:

        // pass CLAWBT as a parameter on contruction so it can access CLAWBT variables
        MyServerCallbacks(CLAWBluetooth* _BT); 

        void onConnect(BLEServer* pServer);
        void onDisconnect(BLEServer* pServer);
};

