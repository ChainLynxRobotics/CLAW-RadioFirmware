#include "src/CLAWBluetooth/CLAWBluetooth.h"
#include "src/CLAWOled/CLAWOled.h"
#include "src/CLAWSD/CLAWSD.h"

CLAWBluetooth BT;
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

  // reccomend starting oled display as the last thing in setup
  // has a 4 second display to show logo and team number because silly :3
  oled.startDisplay();
  Serial.println(BT.getName());
}

void loop() {
  
  // put your main code here, to run repeatedly:
  //Serial.println(BT.getDevices());
  oled.updateDisplay(BT.getName(), BT.getDevices(), BT.getStatus(), CSD.getStatus(), 0);

  // refresh every 50 ms
  delay(50);
}

