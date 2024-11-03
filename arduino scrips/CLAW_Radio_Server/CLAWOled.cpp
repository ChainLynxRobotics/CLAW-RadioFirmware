#include "CLAWOled.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

CLAWOled::CLAWOled() {
    
}

void CLAWOled::updateDisplay(String name, int devices, String status) {

    clear();

    println(name);
    println();
    
    print("Devices connected: ");
    println(devices);
    println();
    
    println(status);
}