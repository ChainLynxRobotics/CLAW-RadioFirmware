#include "CLAWBattery.h"

CLAWBattery::CLAWBattery() {

}

void CLAWBattery::begin(int _batteryPin) {
    batteryPin = _batteryPin;
    pinMode(batteryPin, INPUT);
}

double CLAWBattery::getVoltage() {
    uint32_t Vbatt = 0;
    for(int i = 0; i < 16; i++) {
        Vbatt = Vbatt + analogReadMilliVolts(batteryPin); // ADC with correction   
    }
    float Vbattf = 2 * Vbatt / 16 / 1000.0;     // attenuation ratio 1/2, mV --> V
    Serial.println(Vbattf, 3);
    return Vbattf;
}

int CLAWBattery::getPercent(double voltage) {
    int percent = mapf(voltage, 2.75, 4.2, 1, 20) * 5;
    return percent;
}


// arduino's built in map function uses integer math, which doesnt work with decimals
double CLAWBattery::mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}