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

  // reccomend starting oled display as the last thing in setup
  // has a 4 second display to show logo and team number because silly :3
  oled.startDisplay();
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

  // refresh every half second
  delay(500);

}

