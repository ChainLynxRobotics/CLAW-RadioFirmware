#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class CLAWOled {

    private:


    public:

        CLAWOled();
        void begin();
        void updateDisplay();
}