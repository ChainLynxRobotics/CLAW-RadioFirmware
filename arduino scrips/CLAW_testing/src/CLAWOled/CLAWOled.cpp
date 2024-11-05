#include "CLAWOled.h"

CLAWOled::CLAWOled() {
    
}

// passing parameters from CLAWBT to display on oled screen
void CLAWOled::updateDisplay(String name, int devices, String BTStatus, String LoRaStatus) {

    clear();

    println(name);
    println();
    
    print("Devices connected: ");
    println(devices);
    println();
    
    println(BTStatus);
    println();

    println(LoRaStatus);
}