#include "CLAWOled.h"

CLAWOled::CLAWOled() {
    Adafruit_SSD1306(128, 64, &Wire, -1);
}

void CLAWOled::startDisplay() {

    display();
    clearDisplay();
    delay(10);

    drawBitmap(32, 0, bmp_chainlynx_logo_small, 64, 64, WHITE);
    display();
    delay(3000);

    clearDisplay();
    drawBitmap(0, 0, bmp_8248_logo, 128, 64, WHITE);
    display();
    delay(3000);

}

// passing parameters from CLAWBT to display on oled screen
void CLAWOled::updateDisplay(String name, int devices, int BTStatus, int SDStatus, int LoRaStatus) {

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

    display();
}

void CLAWOled::drawError(int x, int y) {
    drawBitmap(x, y, bmp_error, 16, 16, WHITE);
}