#include <SSD1306Ascii.h>
#include <SSD1306AsciiSoftSpi.h>
#include <SSD1306AsciiSpi.h>
#include <SSD1306AsciiWire.h>
#include <SSD1306init.h>

#include "Arduino.h"

class CLAWOled: public SSD1306AsciiWire{

    private:

    public:

        CLAWOled();
        void updateDisplay(String name, int devices, String status);
};
