# CLAW-RadioFirmware
Firmware for ESP32 based devices powering CLAW's wireless communication.

Allows broadcasting of data packets through [Bluetooth® LE](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE) and [LoRa](https://github.com/sandeepmistry/arduino-LoRa) radio for communication within FRC events without any form of WiFi, enabling rich features of the CLAW Scouting App.

Inspired by [meshtastic](https://meshtastic.org), however this is is custom built from scratch due to meshtastic's [limitation of one phone connection per radio](https://meshtastic.org/docs/introduction/#how-it-works).

# Hardware

This code is designed to run on the [LILYGO T3S3](https://www.amazon.com/LILYGO-ESP32-S3-Development-Wireless-Display/dp/B0BW5W9QXZ), an ESP32-S3 development board with a LoRa module/antenna, Bluetooth® LE 5.0, OLED screen, battery charger, and SD card slot. Perfect for this project!

![LILYGO T3S3](./media/T3S3.jpg?raw=true)

### A Note on Radio Frequencies
This device uses 2.4GHz for Bluetooth® LE and 915MHz for LoRa. For LoRa, Not all radio bands can be used everywhere, the 915MHz band is specifically chosen to comply with USA Radio Laws.


# How It Works

Bluetooth is used for short range communication between phones and radios, while LoRa is used between radios for long range communication (such as between the stands and pit). This allows for many, many phones to be interconnected both short and long distances while using as few of these radios as possible. Because of how this network is built, there is no peer-to-peer, but instead, every message is broadcast for easy and decentralized data sharing.

![Diagram showcasing how different devices are connected throughout the network](./media/diagram.png?raw=true)

## How a message is sent

A Bluetooth-connected phone sets the TX characteristic as the value of its packet.

![Diagram showing an arrow from a phone to a radio](./media/sending_step1.png?raw=true)

Then, the packet is sent via LoRa to other radios, which sets it as the RX characteristic (this also needs to be done for the device sending it.)

![Diagram showing radio sending packet to other radio](./media/sending_step2.png?raw=true)

Finally, all the other devices connected via Bluetooth will be notified of the state change on RX and, hence, receive the packet data.

![Diagram showing radios sending packet to all connected phones](./media/sending_stap3.png?raw=true)

And the message has been broadcast to everybody! Yippee!!!!

# Packet Format

The packet can be **any binary data** that the clients want to send to each other.

#### Bluetooth LE Characteristic Value

| Length      | Data                            |
|-------------|---------------------------------|
| 1-512 bytes | Packet Data (raw bytes)         |

#### LoRa Radio Packets

The data sent over LoRa will have 4 bytes of data appended to the front to identify CLAW packets among other LoRa packets that may be picked up.

| Length      | Data                            |
|-------------|---------------------------------|
| 4 bytes     | 0x8248 (hex) for identification |
| 1-512 bytes | Packet Data (raw bytes)         |

