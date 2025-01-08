#include "src/CLAWBluetooth/CLAWBluetooth.h"
#include "src/CLAWBattery/CLAWBattery.h"
#include "src/CLAWLoRa/CLAWLoRa.h"
#include "src/CLAWOled/CLAWOled.h"
#include "src/CLAWSD/CLAWSD.h"

CLAWBluetooth BT;
CLAWBattery bat;
CLAWLoRa CLoRa(&BT);
CLAWOled oled;
CLAWSD CSD;
// CLAWSD class is defined as CSD because there is an internal refrece to another class called "SD"

void setup() {
  // put your setup code here, to run once:

  // serial for debugging
  Serial.begin(9600);

  // begining bluetooth, SD card, and battery 
  BT.begin();
  CSD.begin();
  CLoRa.begin();
  // pin 1 is internally connected to battery
  // so we pass that as the pin to read voltage
  bat.begin(1);

  // reccomend starting oled display as the last thing in setup
  // has a 3 second display to show team number because silly :3
  oled.startDisplay();
}

void loop() {
  
  // put your main code here, to run repeatedly:
  //Serial.println(BT.getDevices());
  oled.updateDisplay(BT.getName(), BT.getDevices(), BT.getStatus(), CSD.getStatus(), 0, bat.getPercent(bat.getVoltage()));

  if (BT.getDataAvailable()) {
    Serial.println("new data available");
    if(CSD.saveData(BT.getData())) {
      BT.setDataAvailable(false);
    }
  }

  // refresh every 50 ms
  delay(50);
}

