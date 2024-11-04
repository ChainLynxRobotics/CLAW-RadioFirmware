#include "CLAWOled.h"

CLAWOled::CLAWOled() {
    
}

// pass paremeters from CLAWBT to display on oled screen

void CLAWOled::updateDisplay(String name, int devices, String status) {

    clear();

    println(name);
    println();
    
    print("Devices connected: ");
    println(devices);
    println();
    
    println(status);
}