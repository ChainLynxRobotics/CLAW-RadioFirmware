#include "CLAWSD.h"

#define CS 13

CLAWSD::CLAWSD() {
    
}

void CLAWSD::begin() {
    spi.begin(SCK, SDI, SDO, CS);

    if (!SD.begin(CS, spi, 80000000)) {
        Serial.println("Card Mount Failed");
        status = 0;
        return;
    }
}

bool CLAWSD::saveData(String data) {

    // return bool to confirm data was saved 
    return true;
}

int CLAWSD::getStatus() {
    return status;
}