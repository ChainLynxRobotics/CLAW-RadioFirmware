#include "CLAWSD.h"

CLAWSD::CLAWSD() {
    
}

// packages are organized as 32unit packet ID, 8unit 

void CLAWSD::begin() {
    spi.begin(SCK, SDI, SDO, CS);

    // make sure SD card reader is present
    if (!SD.begin(CS, spi, 80000000)) {
        //Serial.println("Card Mount Failed");
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

    uint32_t ID = (uint32_t)data.charAt(3) << 24 | (uint32_t)data.charAt(2) << 16 | (uint32_t)data.charAt(1) << 8 | (uint32_t)data.charAt(0);
    uint8_t index = data.charAt(4);
    uint8_t total = data.charAt(5);

    String packet = data.substring(6);

    Serial.println(ID);
    Serial.println(index);
    Serial.println(total);

    // if(!fs.exists(ID)) {
    //     createFile(ID);
    // } else {
    //     fs.open(ID);
    //     writeData(index, total, packet);
    // }


    // return bool to confirm data was saved 
    return true;
}

int CLAWSD::getStatus() {
    return status;
}

void CLAWSD::createFile(uint32_t fileID) {
    
}

void CLAWSD::writeData(byte _index, byte _total, String _packet) {

}