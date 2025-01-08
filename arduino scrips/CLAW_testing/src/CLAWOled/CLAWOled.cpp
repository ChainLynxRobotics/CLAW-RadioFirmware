#include "CLAWOled.h"

CLAWOled::CLAWOled() : Adafruit_SSD1306(128, 64, &Wire, -1) {
    
}

void CLAWOled::startDisplay() {

    Wire.begin(18, 17);

    begin(SSD1306_SWITCHCAPVCC, 0x3C);
    setTextColor(WHITE);

    display();
    clearDisplay();
    delay(10);

    // displaying logo and team nunmber takes too much boot time :(
    // drawBitmap(32, 0, bmp_chainlynx_logo_small, 64, 64, WHITE);
    // display();
    // delay(3000);

    clearDisplay();
    drawBitmap(0, 0, bmp_8248_logo, 128, 64, WHITE);
    display();
    delay(3000);

}

// passing parameters from CLAWBT to display on oled screen
void CLAWOled::updateDisplay(String name, int devices, int BTStatus, int SDStatus, int LoRaStatus, int batPercent) {

    // clear everything previously displayed and set cursor to 0,0
    clearDisplay();
    setCursor(0, 0);

    // print out radio name at the top of the screen, 
    println(name);
    println();
    
    // display amount of devices connected
    print("Devices connected: ");
    println(devices);
    println();

    // display battery percent in bottom right corner
    // position and display of battery will probably change at some point
    setCursor(65, 57);
    print("%");
    print(batPercent);


    // draw bitmaps by drawBitmap([x position], [y position], [bitmap image], [height], [width], WHITE);
    
    // display Bluetooth status 
    switch (BTStatus) {

        case 0:
            drawBitmap(0, 48, bmp_bluetooth_disconnected, 16, 16, WHITE);
            break;
        
        case 1:
            drawBitmap(0, 48, bmp_bluetooth_connected, 16, 16, WHITE);
            break;

        default:
            drawError(0, 48);
            break;
    }

    // display SD status
    switch (SDStatus) {

        case 0:
            drawBitmap(17, 48, bmp_sd_disconnected, 16, 16, WHITE);
            break;
        
        case 1:
            drawBitmap(17, 48, bmp_sd_connected, 16, 16, WHITE);
            break;

        default:
            drawError(17, 48);
            break;
    }

    // display LoRa status
    switch (LoRaStatus) {

        case 0:
            drawBitmap(33, 48, bmp_LoRa_disconnected, 16, 16, WHITE);
            break;
        
        case 1:
            drawBitmap(33, 48, bmp_LoRa_connected, 16, 16, WHITE);
            break;

        default:
            drawError(33, 48);
            break;
    }

    // displaying battery level
    drawBitmap(49, 48, bmp_battery, 16, 16, WHITE);
    int batteryLevel = map(batPercent, 0, 99, 0, 13);

    for (int i = 0; i <= batteryLevel; i++) {
        drawBitmap(49, 48 - i, bmp_batt_level, 16, 16, WHITE);
    }

    display();
}

// if something for some reason goes wrong, draw an error at the specified coordinates 

void CLAWOled::drawError(int x, int y) {
    drawBitmap(x, y, bmp_error, 16, 16, WHITE);
}