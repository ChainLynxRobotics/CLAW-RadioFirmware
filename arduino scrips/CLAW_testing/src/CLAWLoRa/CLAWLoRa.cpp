#include "CLAWLoRa.h"

CLAWLoRa::CLAWLoRa(CLAWBluetooth *BT) {
    this->BT = BT;
}

void CLAWLoRa::begin() {
    LoRa.setPins(7, 8, 33);

    // setting a sync word so LoRa doesnt messages from other LoRa modules
    LoRa.setSyncWord(0xE5);

    // frequency we're using for LoRa
    // 915 MHz
    LoRa.begin(915E6);

    // setting up callback functions to be called when something 
    // is received and when its done transmitting
    rxCallback = [](int packageSize) {

        String message = "";

        while (LoRa.available()) {
            message += (char)LoRa.read();
        }

        Serial.print("Gateway Receive: ");
        Serial.println(message);
    };

    txDoneCallback = []() {
        CLAWLoRa.setMode(false);
        Serial.println("done transmitting");
    };

    LoRa.onReceive(rxCallback.target<void(*)(int)>);
    LoRa.onTxDone(txDoneCallback.target<void(*)());
    // TX = transmit
    // RX = receive
}

void CLAWLoRa::setMode(bool mode) {

    // true = transmit mode
    // false = recieve mode
    switch (mode) {

        case true:
            LoRa.idle();                          // set standby mode
            LoRa.enableInvertIQ(); 
            break;
        
        case false:
            LoRa.disableInvertIQ();               // normal mode
            LoRa.receive(); 
            break;
    }
}

void CLAWLoRa::sendPacket(String packet) {
    setMode(true);
    LoRa.beginPacket();
    LoRa.print(packet);
    LoRa.endPacket(true);
}

int CLAWLoRa::getStatus() {

}