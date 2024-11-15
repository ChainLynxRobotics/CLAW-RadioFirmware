#include "src/CLAWBluetooth/CLAWBluetooth.h"
#include "src/CLAWOled/CLAWOled.h"
#include "src/CLAWSD/CLAWSD.h"

CLAWBluetooth BT;
CLAWOled oled;
CLAWSD CSD;

void setup() {
  // put your setup code here, to run once:

  // serial for debugging
  Serial.begin(9600);

  // begining bluetooth and SD card
  BT.begin();
  CSD.begin();

  // begin oled with type of oled module (SSD1306), and its I2C address (0x3C)
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);

  oled.startDisplay();

  delay(200);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  Serial.println(BT.getDevices());
  oled.updateDisplay(BT.getName(), BT.getDevices(), BT.getStatus(), CSD.getStatus(), 0);

  // if (SD.saveData(BT.getData)) {
  //   Serial.println("data saved");
  // } else {
  //   Serial.println("something went wrong");
  // }

  // display updates every 2.5 seconds
  delay(2500);

}

