#include "Arduino.h"

// #include <SPI.h>
// #include <SD.h>
// add these things back in later, its just being weird and i want the code that works to compile

class CLAWSD/*: public SDLib::SDClass*/ {

    private:

    public:

        CLAWSD();
        bool saveData(String data);
};