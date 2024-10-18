# CLAW-RadioFirmware
Firmware for ESP32 based devices powering CLAW's wireless communication.

Allows broadcasting of data packets through Bluetooth® LE and LoRa radio for communication within FRC events without any form of WiFi, enabling rich features of the CLAW Scouting App.

Inspired by [meshtastic](https://meshtastic.org), however this is is custom built from scratch due to meshtastic's [limitation of one phone connection per radio](https://meshtastic.org/docs/introduction/#how-it-works).

# Hardware

This code is designed to run on the [LILYGO T3S3](https://www.amazon.com/LILYGO-ESP32-S3-Development-Wireless-Display/dp/B0BW5W9QXZ), an ESP32-S3 development board with a LoRa module/antenna, Bluetooth® LE 5.0, OLED screen, battery charger, and SD card slot. Perfect for this project!

![LILYGO T3S3](./media/T3S3.jpg?raw=true)

### A Note on Radio Frequencies
This device uses 2.4GHz for Bluetooth® LE and 915MHz for LoRa. For LoRa, Not all radio bands can be used everywhere, the 915MHz band is specifically chosen to comply with USA Radio Laws.


# How It Works

Bluetooth is used for short range communication between phones and radios, while LoRa is used between radios for long range communication (such as between the stands and pit). This allows for many many phones to be interconnected both short and long distance while using as few of these radios as possible.

![Diagram showcasing how different devices are connected throughout the network](./media/diagram.png?raw=true)