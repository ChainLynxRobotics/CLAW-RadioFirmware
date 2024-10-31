/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updated by chegewara

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
   And has a characteristic of: beb5483e-36e1-4688-b7f5-ea07361b26a8

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   A connect hander associated with the server starts a background task that performs notification
   every couple of seconds.
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

//LoRa Setup

#include <LoRa.h>
#include "LoRaBoards.h"

#ifndef CONFIG_RADIO_FREQ
#define CONFIG_RADIO_FREQ           868.0
#endif
#ifndef CONFIG_RADIO_OUTPUT_POWER
#define CONFIG_RADIO_OUTPUT_POWER   17
#endif
#ifndef CONFIG_RADIO_BW
#define CONFIG_RADIO_BW             125.0
#endif

#if !defined(USING_SX1276) && !defined(USING_SX1278)
#error "LoRa example is only allowed to run SX1276/78. For other RF models, please run examples/RadioLibExamples
#endif

//OLED Display Setup

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String amount_of_devices_connected = "0 Devices Connected";
String current_progress = "Waiting for data...";
String error_message = "No errors";

//SD Card Setup

#include <SPI.h>
#include <SD.h>

const int chipSelect = 13; // Pin for SD card


BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
uint32_t value = 0;
String serverName;
bool location;
bool transmit_mode = false;

// TODO
// set up password stuff
// transmit over LoRa
// explain same-script and hardware differentiability stuff



// Service ID, should be the same as the client so the client knows which device to connect to.
#define SERVICE_UUID              "82480000-9a25-49fc-99be-2c16d1492d35"

// Keys for the clients to update
// We use two characteristics to transmit data to and from CLAW clients
// characteristic_recive, what we'll be refering to as RX, recives scouting data from individual clients
// characteristic_transmit, TX, transmits recived data to every other client that is connected to one of the ESP radios

#define CHARACTERISTIC_TRANSMIT  "82480001-9a25-49fc-99be-2c16d1492d35"
#define CHARACTERISTIC_RECIVE    "82480002-9a25-49fc-99be-2c16d1492d35"


// Characteristic pointers
BLECharacteristic *pCharacteristicTransmit;
BLECharacteristic *pCharacteristicRecive;


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
    }
};



void setup() {
  Serial.begin(115200);

  //debugging
  location = true;

  if (location) {
    serverName = "CLAW Radio - Stands";
  } else {
    serverName ="CLAW Radio - Pit";
  }

  // Create the BLE Device with name
  // 
  BLEDevice::init(serverName.c_str());

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

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");

  setup_LoRa();


  //OLED Display Setup

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.display();

  updateDisplay();

  //SD Card Setup

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    error_message = "SD card initialization failed!";
    updateDisplay();
    return;
  }
  Serial.println("SD card initialized");

}

void loop() {
    // Example LoRa receiver code

    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // received a packet
        Serial.print("Received packet '");

        String recv = "";
        // read packet
        while (LoRa.available()) {
            recv += (char)LoRa.read();
        }

        Serial.println(recv);

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
        if (u8g2) {
            u8g2->clearBuffer();
            char buf[256];
            u8g2->drawStr(0, 12, "Received OK!");
            u8g2->drawStr(0, 26, recv.c_str());
            snprintf(buf, sizeof(buf), "RSSI:%i", LoRa.packetRssi());
            u8g2->drawStr(0, 40, buf);
            snprintf(buf, sizeof(buf), "SNR:%.1f", LoRa.packetSnr());
            u8g2->drawStr(0, 56, buf);
            u8g2->sendBuffer();
        }
    }
}

void setup_LoRa() {
    setupBoards();
    // When the power is turned on, a delay is required.
    delay(1500);

    Serial.println("LoRa Receiver");

#ifdef  RADIO_TCXO_ENABLE
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);
#endif

    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
    if (!LoRa.begin(CONFIG_RADIO_FREQ * 1000000)) {
        Serial.println("Starting LoRa failed!");
	error_message = "Starting LoRa failed!";
	updateDisplay();
        while (1);
    }

    LoRa.setTxPower(CONFIG_RADIO_OUTPUT_POWER);

    LoRa.setSignalBandwidth(CONFIG_RADIO_BW * 1000);

    LoRa.setSpreadingFactor(10);

    LoRa.setPreambleLength(16);

    LoRa.setSyncWord(0xAB);

    LoRa.disableCrc();

    LoRa.disableInvertIQ();

    LoRa.setCodingRate4(7);
    
    // put the radio into receive mode
    LoRa.receive();

}

void transmit_data_via_LoRa(String data) {
    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket();
}

void updateDisplay() {
  display.clearDisplay();

  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println(serverName);

  display.setCursor(0, 10);
  display.println(amount_of_devices_connected);

  display.setCursor(0, 20);
  display.println(current_progress);

  display.setCursor(0, 30);
  display.println(error_message);

  display.display();
}

void save_data_to_SD(String data) {
  File dataFile = SD.open("transmissions.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  } else {
    Serial.println("Failed to open transmission.txt for writing.");
    error_message = "Failed to open transmission.txt for writing.";
    updateDisplay();
  }  
}

