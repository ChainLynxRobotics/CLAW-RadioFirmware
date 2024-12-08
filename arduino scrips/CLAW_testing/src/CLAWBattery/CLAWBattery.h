#include "Arduino.h"

class CLAWBattery {

    private:

        int batteryPin;

    public:

        CLAWBattery();
        void begin(int _batteryPin);
        double getVoltage();
        int getPercent(double voltage);
        double mapf(double x, double in_min, double in_max, double out_min, double out_max);
};