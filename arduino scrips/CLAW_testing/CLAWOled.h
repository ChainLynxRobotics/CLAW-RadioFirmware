#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 32

class CLAWOled: public Adafruit_SSD1306 {

    private:

      //Adafruit_SSD1306 display(128, 32, &Wire, -1);

    public:

        CLAWOled();
        //void begin();
        void updateDisplay(String name, int devices, String status);
};

// class Adafruit_SSD1306 {


// }