#include "CLAWBluetooth.h"
#include "CLAWOled.h"

CLAWBluetooth BT;
CLAWOled display;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin();
  display.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println(BT.getDevices());
  display.updateDisplay(BT.getName(), BT.getDevices(), BT.status);
}
