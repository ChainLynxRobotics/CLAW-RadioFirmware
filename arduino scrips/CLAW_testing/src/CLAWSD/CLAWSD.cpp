#include "CLAWSD.h"

CLAWSD::CLAWSD() {
    
}

// packages are organized as 32unit packet ID, 8unit 

void CLAWSD::begin() {
    spi.begin(SCK, SDI, SDO, CS);

    // make sure SD card reader is present
    if (!SD.begin(CS, spi, 80000000)) {
        Serial.println("Card Mount Failed");
        status = 0;
        return;

    } else {
        // get the type of SD card 
        uint8_t cardType = SD.cardType();

        // make sure SD card is in the reader
        if (cardType == CARD_NONE) {
            Serial.println("No SD card attached");
            status = 0;
            return;
        }

        status = 1;
    }


}

bool CLAWSD::saveData(String data) {

    // return bool to confirm data was saved 
    return true;
}

int CLAWSD::getStatus() {
    return status;
}