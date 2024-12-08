#include "WString.h"
#include "CLAWBluetooth.h"

// UUID for the CLAW radio
#define SERVICE_UUID             "82480000-9a25-49fc-99be-2c16d1492d35"

// UUIDs for the characteristics we use
//       1 -> TX      2 -> RX
#define CHARACTERISTIC_TRANSMIT  "82480001-9a25-49fc-99be-2c16d1492d35"
#define CHARACTERISTIC_RECIVE    "82480002-9a25-49fc-99be-2c16d1492d35"

CLAWBluetooth::CLAWBluetooth()
{
    // i dont think any code is needed in the constructor methood
}

void CLAWBluetooth::begin() {
    // pinMode(46, INPUT);
    // initialize Bluetooth device with name returned from setName();
    // BLE sometimes uses weird string types, sometimes you may need to pass [String].c_str()
    BLEDevice::init(setName().c_str());

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
    Serial.println(getName());
}

// Characteristic pointers
BLECharacteristic *pCharacteristicTransmit;
BLECharacteristic *pCharacteristicRecive;

// setName is called on start and checks if pin [probably gpio 46] is connected to 3.3v or ground via 1k resistor
//       3.3v - Stands
//       GND - Pit
String CLAWBluetooth::setName() {
    //implement hardware differentiation code here
    //Claw Radio - Stands / Pit
    // switch (digitalRead(46))
    // {
    // case HIGH:
    //     deviceName += "Stands";
    //     break;
    
    // case LOW:
    //     deviceName += "Pit";
    //     break;

    // default:
    //     deviceName += "Test";
    // }

    return deviceName += "Test";
}

String CLAWBluetooth::getName() {
    return deviceName;
}

void CLAWBluetooth::setStatus(int newStatus) {
    status = newStatus;
}


int CLAWBluetooth::getStatus() {
    return status;
}

int CLAWBluetooth::getDevices() {
    return deviceConnected;
}

String CLAWBluetooth::getData() {
    return pCharacteristicTransmit->getValue();
}

void CLAWBluetooth::setDataAvailable(bool state) {
    newData = state;
}

bool CLAWBluetooth::getDataAvailable() {
    return newData;
}

MyServerCallbacks::MyServerCallbacks(CLAWBluetooth* _BT) {
  BT = _BT;
}

void MyServerCallbacks::onConnect(BLEServer* pServer) {
    BLEDevice::startAdvertising();
    Serial.println("device connected");
    BT->deviceConnected++;

    if (BT->deviceConnected > 0) {
        BT->setStatus(1);
    }
}

// keeping track of the amount of connected devices ^ v

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
    Serial.println("device disconnected");
    BT->deviceConnected--;
    
    if (BT->deviceConnected <= 0) {
        BT->setStatus(0);
    }
}

CharacteristicChangeCallbacks::CharacteristicChangeCallbacks(CLAWBluetooth* _BT) {
  BT = _BT;
}

void CharacteristicChangeCallbacks::onWrite(BLECharacteristic *pCharacteristic) {

    // Get the key value pair, the key is one of the characteristic UUIDs defined earlier
    String key = pCharacteristic->getUUID().toString();
    String value = pCharacteristic->getValue();

    // set TX to RX value, then notify TX has been changed
    BT->pCharacteristicTransmit->setValue(pCharacteristic->getValue());
    BT->pCharacteristicTransmit->notify();
    BT->setDataAvailable(true);

    // print to serial for debugging
    Serial.println("characteristic changed");

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
}