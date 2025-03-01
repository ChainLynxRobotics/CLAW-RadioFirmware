#include "CLAWLoRa.h"

CLAWLoRa::CLAWLoRa() {
}

void CLAWLoRa::begin() {

	setStatus(0);

	hwConfig.CHIP_TYPE = SX1262_CHIP;		  // Example uses an eByte E22 module with an SX1262
	hwConfig.PIN_LORA_RESET = RST; // LORA RESET
	hwConfig.PIN_LORA_NSS = CS;	 // LORA SPI CS
	hwConfig.PIN_LORA_SCLK = SCK;   // LORA SPI CLK
	hwConfig.PIN_LORA_MISO = SDI;   // LORA SPI MISO
	hwConfig.PIN_LORA_DIO_1 = DIO; // LORA DIO_1
	// hwConfig.PIN_LORA_BUSY = PIN_LORA_BUSY;   // LORA SPI BUSY
	hwConfig.PIN_LORA_MOSI = SDO;   // LORA SPI MOSI
	hwConfig.RADIO_TXEN = -1;		  // LORA ANTENNA TX ENABLE
	hwConfig.RADIO_RXEN = -1;		  // LORA ANTENNA RX ENABLE

	Serial.println("set hardware config");

    lora_hardware_init(hwConfig);

	Serial.println("initialized hardware config");

    RadioEvents.TxDone = OnTxDone;
	RadioEvents.RxDone = OnRxDone;

	Serial.println("set TX/RX callbacks");
	// RadioEvents.TxTimeout = OnTxTimeout;
	// RadioEvents.RxTimeout = OnRxTimeout;
	// RadioEvents.RxError = OnRxError;
	// RadioEvents.CadDone = OnCadDone;

	Radio.Init(&RadioEvents);

	// Set Radio channel
	Radio.SetChannel(RF_FREQUENCY);


	Radio.SetCustomSyncWord(8248);


	// Set Radio TX configuration
	Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
					  LORA_SPREADING_FACTOR, LORA_CODINGRATE,
					  LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
					  true, 0, 0, LORA_IQ_INVERSION_ON, TX_TIMEOUT_VALUE);


	// Set Radio RX configuration
	Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
					  LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
					  LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
					  0, true, 0, 0, LORA_IQ_INVERSION_ON, true);


    Radio.Rx(RX_TIMEOUT_VALUE);

	delay(100);
	yield();

	setStatus(1);
}

void CLAWLoRa::setMode(bool mode) {

}

void CLAWLoRa::sendPacket(String _packet) {

	//Serial.println(_packet.charAt(0));

	for (int i = 0; i < _packet.length(); i++) {
		TxdBuffer[i] = _packet.charAt(i);
		Serial.print(TxdBuffer[i]);
		Serial.print(", ");
	}
	
	Radio.Send(TxdBuffer, BufferSize);

}

int CLAWLoRa::getStatus() {
    return status;
}

void CLAWLoRa::setStatus(int _status) {
	status = _status;
}

void CLAWLoRa::OnTxDone() {

}

void CLAWLoRa::OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {

	for (int i = 0; i < size; i++) {
		Serial.println(payload[i]);
	}
}