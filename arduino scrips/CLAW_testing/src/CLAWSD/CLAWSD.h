#include "Arduino.h"

// #include "FS/src/FS.h"
// #include "SPI/src/SPI.h"
// #include "SD/src/SD.h"

#include <FS.h>
#include <SPI.h>
#include <SD.h>

// using SDO (Serial Data Out) and SDI (Serial Data In) instead of previous SPI terms
// MISO and MOSI are outdated and have bad historical connotations

// testing pins on esp32 dev module
// #define SCK 14
// #define SDI 12
// #define SDO 13
// #define CS 15

// actual pin for lilygo module
#define SCK 14
#define SDI 2
#define SDO 11
#define CS 13

class CLAWSD {

    private:

    SPIClass spi = SPIClass(HSPI);
    int status = 0;
    uint32_t ID;
    //File file = fs.open("/")

    public:
    
        CLAWSD();

        void begin();
        bool saveData(String data);
        int getStatus();
        void createFile(uint32_t fileID);
        void writeData(byte _index, byte _total, String _packet);
};