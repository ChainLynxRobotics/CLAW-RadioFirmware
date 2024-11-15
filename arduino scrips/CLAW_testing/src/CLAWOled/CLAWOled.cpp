#include "CLAWOled.h"

CLAWOled::CLAWOled() {
    
}

void CLAWOled::startDisplay() {

    display();
    clearDisplay();

}

// passing parameters from CLAWBT to display on oled screen
void CLAWOled::updateDisplay(String name, int devices, int BTStatus, int SDStatus, int LoRaStatus) {

    // clear everything previously displayed and set cursor to 0,0
    clearDisplay();

    // print out radio name at the top of the screen, 
    println(name);
    println();
    
    // display amount of devices connected
    print("Devices connected: ");
    println(devices);
    println();
    
    // status of bluetooth (under development)
    println(BTStatus);
    println();

    // status of LoRa communication (under development)
    println(LoRaStatus);
    display();
}