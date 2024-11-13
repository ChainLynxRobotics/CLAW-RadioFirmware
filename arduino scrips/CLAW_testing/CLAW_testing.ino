#include "src/CLAWBluetooth/CLAWBluetooth.h"
#include "src/CLAWOled/CLAWOled.h"
#include "src/CLAWSD/CLAWSD.h"

CLAWBluetooth BT;
CLAWOled oled;
CLAWSD SD;

void setup() {
  // put your setup code here, to run once:

  // serial for debugging
  Serial.begin(9600);

  // begining bluetooth and SD card, SD uses pin [4] for SPI chip select
  BT.begin();
  SD.begin(4);

  // begin oled with type of oled module (128x64), and its I2C address (0x3C)
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);

  oled.startDisplay();

  delay(200);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  Serial.println(BT.getDevices());
  oled.updateDisplay(BT.getName(), BT.getDevices(), BT.getStatus(), /*placeholder message -> */ "[LoRa status]");

  if (SD.saveData(BT.getData)) {
    Serial.println("data saved");
  } else {
    Serial.println("something went wrong");
  }

  // display updates every 2.5 seconds
  delay(2500);

}

