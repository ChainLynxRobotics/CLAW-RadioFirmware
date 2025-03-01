#include "CLAWBattery.h"

CLAWBattery::CLAWBattery() {
    // all this class does is read the voltage on pin 1
    // pin 1 is internally connected to the battery with a voltage divider
    // then does some math to get the average voltage and converts that to a percent
}

void CLAWBattery::begin() {
    // setting battery pin to input so we can read it
    pinMode(1, INPUT);
}

double CLAWBattery::getVoltage() {
    uint32_t Vbatt = 0;
    // finding the average voltage from 16 samples
    for(int i = 0; i < 16; i++) {
        Vbatt = Vbatt + analogReadMilliVolts(1); // ADC with correction   
    }
    // dividing by the sample size, and 1000 to convert milivolts to volts
    float Vbattf = 2 * Vbatt / 16 / 1000.0;     // attenuation ratio 1/2, mV --> V

    // rounding voltage to 2 decimal points so percentage jitters around a little less
    float VbattfRound = round(Vbattf * 100) / 100;
    //Serial.println(VbattfRound, 2);
    return VbattfRound;
}

int CLAWBattery::getPercent(double voltage) {
    // constaining max percentage to 99 because 3 digits doesnt fit onscreen
    int percent = constrain(mapf(voltage, 2.75, 4.17, 1, 25) * 4, 0, 99);
    return percent;
}


// arduino's built in map function uses integer math, which doesnt work with decimals
double CLAWBattery::mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}