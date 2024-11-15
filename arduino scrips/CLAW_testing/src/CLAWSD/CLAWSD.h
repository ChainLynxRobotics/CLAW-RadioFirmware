#include "Arduino.h"

// #include "FS/src/FS.h"
// #include "SPI/src/SPI.h"
// #include "SD/src/SD.h"

#include <FS.h>
#include <SPI.h>
#include <SD.h>

// using SDO (Serial Data Out) and SDI (Serial Data In) instead of previous SPI terms
//  MISO and MOSI are outdated and have bad historical connotations
#define SCK 18
#define SDI 19
#define SDO 23
#define CS 5
// actual lilygo pins are CS 13, SDO 11, SCK 14, SDI 2

class CLAWSD {

    private:

    SPIClass spi = SPIClass(VSPI);
    int status = 0;

    public:

        //File currentFile;

        CLAWSD();

        // pass chip select pin on begin
        void begin();
        bool saveData(String data);
        int getStatus();
};