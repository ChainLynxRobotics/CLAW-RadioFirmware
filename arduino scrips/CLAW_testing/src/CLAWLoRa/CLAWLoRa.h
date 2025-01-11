#include "Arduino.h"
#include <LoRa.h>
#include "src/CLAWBluetooth/CLAWBluetooth.h" 


class CLAWLoRa {

    private:

        static CLAWLoRa* instance;
        static void rxCallback(int packageSize);
        static void txDoneCallback();

        CLAWBluetooth *BT;

        int status = 0;
        int frequency;
        void setMode(bool mode);

    public:

        CLAWLoRa(CLAWBluetooth *BT);
        void begin();
        int getStatus();
        void sendPacket(String message);

};