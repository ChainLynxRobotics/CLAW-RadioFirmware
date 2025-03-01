#include "src/CLAWBluetooth/CLAWBluetooth.h"
#include "src/CLAWBattery/CLAWBattery.h"
#include "src/CLAWLoRa/CLAWLoRa.h"
#include "src/CLAWOled/CLAWOled.h"
#include "src/CLAWSD/CLAWSD.h"

#define VERSION 1.00

CLAWBluetooth BT;
CLAWBattery bat;
CLAWLoRa CLoRa;
CLAWOled oled;
CLAWSD CSD;

bool deviceLocation;
// CLAWSD class is defined as CSD because there is an internal refrece to another class called "SD"

void setup() {

  Serial.begin(9600);
  //Serial.println("device on");

  // put your setup code here, to run once:

  // reads pin 46, which is either connected to 3.3v or ground
  // when connected to ground, it is set as the pit server
  // and connected to 3.3v, the stands server
  // both modules use this same script, but we're able to
  // differentiate them through hardware

  pinMode(46, INPUT);
  switch (digitalRead(46)) {
    
    case HIGH: 
      deviceLocation = true;
      break;

    case LOW:
      deviceLocation = false;
      break;

    default:
      break;
  }

  BT.setName(deviceLocation);

  // begining bluetooth, SD card, and battery 
  // SD library doesnt work
  BT.begin();
  CSD.begin();
  bat.begin();

  oled.startDisplay(VERSION);

  oled.updateDisplay(BT.getName(), BT.getDevices(), BT.getStatus(), CSD.getStatus(), 0, bat.getPercent(bat.getVoltage()));


  // LoRa takes a minute to set up, and i couldnt figure out how to multithreadd
  CLoRa.begin();

}

void loop() {
  
  // updating oled display every loop
  // pretty inneficient but it works fine for now

  oled.updateDisplay(BT.getName(), BT.getDevices(), BT.getStatus(), CSD.getStatus(), CLoRa.getStatus(), bat.getPercent(bat.getVoltage()));

  if (BT.getDataAvailable()) {

    Serial.println("new data available");
    CLoRa.sendPacket(BT.getData());
    BT.setDataAvailable(false);
    
  }

  // refresh every 50 ms
  delay(50);
}

