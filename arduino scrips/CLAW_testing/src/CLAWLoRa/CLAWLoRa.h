#include "Arduino.h"
#include <LoRa.h>
#include "src/CLAWBluetooth/CLAWBluetooth.h" 


class CLAWLoRa {

    private:

        int status = 0;
        int frequency;

        void setMode(bool mode);

        CLAWBluetooth *BT;

        std::function<void()> txDoneCallback;
        std::function<void(int packageSize)> rxCallback; 

    public:

        CLAWLoRa(CLAWBluetooth *BT);
        void begin();
        int getStatus();
        void sendPacket(String message);

};