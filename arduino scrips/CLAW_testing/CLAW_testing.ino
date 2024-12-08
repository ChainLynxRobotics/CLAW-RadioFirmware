#include "src/CLAWBluetooth/CLAWBluetooth.h"
#include "src/CLAWBattery/CLAWBattery.h"
#include "src/CLAWOled/CLAWOled.h"
#include "src/CLAWSD/CLAWSD.h"

CLAWBluetooth BT;
CLAWBattery bat;
CLAWOled oled;
CLAWSD CSD;
// CLAWSD class is defined as CSD because there is an inter refrece to another class called "SD"

void setup() {
  // put your setup code here, to run once:

  // serial for debugging
  Serial.begin(9600);

  // begining bluetooth and SD card
  BT.begin();
  CSD.begin();
  bat.begin(1);

  // reccomend starting oled display as the last thing in setup
  // has a 4 second display to show logo and team number because silly :3
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

