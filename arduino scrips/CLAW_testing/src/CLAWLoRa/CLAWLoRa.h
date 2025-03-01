#include "Arduino.h"
#include <SPI.h>
#include <SX126x-Arduino.h>
//#include <Arduino_FreeRTOS.h>

#define RF_FREQUENCY 868000000  // Hz
#define TX_OUTPUT_POWER 22		// dBm
#define LORA_BANDWIDTH 0		// [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR 7 // [SF7..SF12]
#define LORA_CODINGRATE 1		// [1: 4/5, 2: 4/6,  3: 4/7,  4: 4/8]
#define LORA_PREAMBLE_LENGTH 8  // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT 0   // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false
#define RX_TIMEOUT_VALUE 3000
#define TX_TIMEOUT_VALUE 3000

#define BUFFER_SIZE 255

#define SCK 5
#define SDI 3
#define SDO 6
#define CS 7
#define DIO 33
#define RST 8


class CLAWLoRa{

    private:

        hw_config hwConfig;


        int status = 0;
        int frequency;
        void setMode(bool mode);
        uint16_t BufferSize = BUFFER_SIZE;
        uint8_t TxdBuffer[BUFFER_SIZE];


    public:

        RadioEvents_t RadioEvents; 

        CLAWLoRa();
        void begin();
        int getStatus();
        void setStatus(int _status);
        void sendPacket(String package);

        static void OnTxDone();
        static void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
        // void OnTxTimeout(void);
        // void OnRxTimeout(void);
        // void OnRxError(void);
        // void OnCadDone(bool cadResult);

};