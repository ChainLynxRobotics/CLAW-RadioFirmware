#include "WString.h"
#include "CLAWBluetooth.h"

#define SERVICE_UUID             "82480000-9a25-49fc-99be-2c16d1492d35"

#define CHARACTERISTIC_TRANSMIT  "82480001-9a25-49fc-99be-2c16d1492d35"
#define CHARACTERISTIC_RECIVE    "82480002-9a25-49fc-99be-2c16d1492d35"

CLAWBluetooth::CLAWBluetooth()
{
    
}

void CLAWBluetooth::begin() {
    BLEDevice::init(getName().c_str());

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks(this));

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristicTransmit = pService->createCharacteristic(
                        CHARACTERISTIC_TRANSMIT,
                        BLECharacteristic::PROPERTY_READ   |
                        BLECharacteristic::PROPERTY_WRITE  |
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_INDICATE
                        );

    pCharacteristicRecive = pService->createCharacteristic(
                        CHARACTERISTIC_RECIVE,
                        BLECharacteristic::PROPERTY_READ   |
                        BLECharacteristic::PROPERTY_WRITE  |
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_INDICATE
                        );

    // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
    // Create a BLE Descriptor
    pCharacteristicTransmit->addDescriptor(new BLE2902());
    pCharacteristicRecive->addDescriptor(new BLE2902());

    // Tells both characteristics to use the same callback methods we defined above to listen for changes
    CharacteristicChangeCallbacks *callbacks = new CharacteristicChangeCallbacks(this);
    pCharacteristicTransmit->setCallbacks(callbacks);
    pCharacteristicRecive->setCallbacks(callbacks);

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}

// Characteristic pointers
BLECharacteristic *pCharacteristicTransmit;
BLECharacteristic *pCharacteristicRecive;

String CLAWBluetooth::getName() {
    //implement hardware differentiation code
    //Claw Radio - Stands / Pit
    return "CLAW Radio - Stands";
}

int CLAWBluetooth::getDevices() {
    return deviceConnected;
}

MyServerCallbacks::MyServerCallbacks(CLAWBluetooth* _BT) {
  BT = _BT;
}

void MyServerCallbacks::onConnect(BLEServer* pServer) {
    BLEDevice::startAdvertising();
    Serial.println("device connected");
    BT->deviceConnected++;
};

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
    Serial.println("device disconnected");
    BT->deviceConnected--;
}

CharacteristicChangeCallbacks::CharacteristicChangeCallbacks(CLAWBluetooth* _BT) {
  BT = _BT;
}


void CharacteristicChangeCallbacks::onWrite(BLECharacteristic *pCharacteristic) {

    // Get the key value pair, the key is one of the characteristic UUIDs defined earlier
    String key = pCharacteristic->getUUID().toString();
    String value = pCharacteristic->getValue();
    Serial.println("characteristic changed");
    BT->pCharacteristicTransmit->setValue(pCharacteristic->getValue());
    BT->pCharacteristicTransmit->notify();

    // Debug messages
    // if (value.length() > 0) {
    // Serial.println("*********");

    // Serial.print("Key:   ");
    // for (int i = 0; i < key.length(); i++) Serial.print(key[i]);
    // Serial.println();

    // Serial.print("Value: ");
    // for (int i = 0; i < value.length(); i++) Serial.print(value[i]);
    // Serial.println();

    // Serial.println("*********");
    // }
};

