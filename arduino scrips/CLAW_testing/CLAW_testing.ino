#include "CLAWBluetooth.h"

CLAWBluetooth BT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println(BT.getDevices());
}
