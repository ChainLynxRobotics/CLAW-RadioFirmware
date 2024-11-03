#include "CLAWOled.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

CLAWOled::CLAWOled() {

}

void CLAWOled::begin() {

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C)
}

void CLAWOled::updateDisplay(String name, int devices, String status) {

    display.setCursor(0, 0);
    display.print(name);

    display.setCursor(0, 10);
    display.print("Devices connected: ");
    display.print(devices):

    display.setCursor(0, 20);
    display.print(status);
}