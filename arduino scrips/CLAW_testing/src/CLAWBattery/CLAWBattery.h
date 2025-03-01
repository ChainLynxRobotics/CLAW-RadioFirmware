#include "Arduino.h"

class CLAWBattery {

    private:

    public:

        CLAWBattery();
        void begin();
        // seperate function for getting voltage vs getting percentage
        // because idk, we might need voltage for some reason
        double getVoltage();
        int getPercent(double voltage);
        double mapf(double x, double in_min, double in_max, double out_min, double out_max);
};