#include "CLAWBluetooth.h"

#define SERVICE_UUID             "82480000-9a25-49fc-99be-2c16d1492d35"

#define CHARACTERISTIC_TRANSMIT  "82480001-9a25-49fc-99be-2c16d1492d35"
#define CHARACTERISTIC_RECIVE    "82480002-9a25-49fc-99be-2c16d1492d35"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
u_int32_t value = 0;
int deviceConnected = 0;

CLAWBluetooth::CLAWBluetooth() {
    BLEDevice::init(serverName().c_str());

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

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
    CharacteristicChangeCallbacks *callbacks = new CharacteristicChangeCallbacks();
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

String CLAWBluetooth::serverName() {
    //implement hardware differentiation code
    //Claw Radio - Stands / Pit
    return "CLAW Radio - Stands";
}


void MyServerCallbacks::onConnect(BLEServer* pServer) {
    BLEDevice::startAdvertising();
    deviceConnected++;
};

void MyServerCallbacksonDisconnect(BLEServer* pServer) {
    deviceConnected--;
}


void CharacteristicChangeCallbacks::onWrite(BLECharacteristic *pCharacteristic) {

    // Get the key value pair, the key is one of the characteristic UUIDs defined earlier
    std::string key = pCharacteristic->getUUID().toString();
    std::string value = pCharacteristic->getValue();
    Serial.println("characteristic changed");
    pCharacteristicTransmit->setValue(pCharacteristic->getValue());

    // Debug messages
    /*if (value.length() > 0) {
    Serial.println("*********");

    Serial.print("Key:   ");
    for (int i = 0; i < key.length(); i++) Serial.print(key[i]);
    Serial.println();

    Serial.print("Value: ");
    for (int i = 0; i < value.length(); i++) Serial.print(value[i]);
    Serial.println();

    Serial.println("*********");
    }*/
};

