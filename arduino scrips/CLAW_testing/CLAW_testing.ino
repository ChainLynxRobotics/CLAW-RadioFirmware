#include "CLAWBluetooth.h"
#include "CLAWOled.h"

CLAWBluetooth BT;
CLAWOled oled;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin();

  Wire.begin();
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(Adafruit5x7);
  delay(200);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  Serial.println(BT.getDevices());
  oled.updateDisplay(BT.getName(), BT.getDevices(), BT.status);
  //display updates every 2.5 seconds
  delay(2500);

}
