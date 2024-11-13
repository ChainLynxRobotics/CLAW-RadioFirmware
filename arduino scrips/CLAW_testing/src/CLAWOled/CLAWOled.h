#include <Adafruit_SSD1306.h>
#include <splash.h>

#include "Arduino.h"

// remember to put all global variables and funtions in its .h file !

// this script isnt complicated, put its good practice to put it in its own C++ file

class CLAWOled: public Adafruit_SSD1306{

    private:

    public:

        CLAWOled();
        void startDisplay();
        void updateDisplay(String name, int devices, String BTStatus, String LoRaStatus);
};
