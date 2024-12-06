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

    byte dataArray[data.length()];

    for(int i = 0; i < data.length(); i++) {
        dataArray[i] = data.charAt(i);
    }

    ID = dataArray[0] << 24 + dataArray[1] << 16 + dataArray[2] << 8 + dataArray[3];
    index = dataArray[4];
    total = dataArray[5];
    
    for(int i = 0; i < data.length() - 6; i++) {
        packet += data.charAt(i);
    }

    if (!fs.exists(ID)) {
        createFile(ID);
    }



    // return bool to confirm data was saved 
    return true;
}

int CLAWSD::getStatus() {
    return status;
}

void CLAWSD::createFile(uint32_t fileID) {
    
}

void CLAWSD::appendData(byte _index, byte _total, String _packet)