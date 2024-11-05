#include "Arduino.h"

#include <SPI.h>
#include <SD.h>

class CLAWSD: public SD {

    private:

    public:

        CLAWSD();
        bool saveData(String data);
}