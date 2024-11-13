#include "Arduino.h"

//#include <SPI.h>
//#include <SD.h>
// add these things back in later, its just being weird and i want the code that works to compile

class CLAWSD/*: public SDLib::SDClass*/ {

    private:

    public:

        File currentFile;

        CLAWSD();

        // pass chip select pin on begin
        void begin(int cs);
        bool saveData(String data);
};