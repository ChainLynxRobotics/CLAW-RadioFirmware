#include <SSD1306Ascii.h>
#include <SSD1306AsciiSoftSpi.h>
#include <SSD1306AsciiSpi.h>
#include <SSD1306AsciiWire.h>
#include <SSD1306init.h>

#include "Arduino.h"

// remember to put all global variables and funtions in its .h file !

// this script isnt complicated, put its good practice to put it in its own C++ file

class CLAWOled: public SSD1306AsciiWire{

    private:

    public:

        CLAWOled();
        void updateDisplay(String name, int devices, String status);
};
