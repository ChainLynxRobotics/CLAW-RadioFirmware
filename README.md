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

A Bluetooth-connected phone sets the RX characteristic as the value of its packet.

![Diagram showing an arrow from a phone to a radio](./media/sending_step1.png?raw=true)

Then, the packet is sent via LoRa to other radios, which sets it as the TX characteristic (this also needs to be done for the device sending it.)

![Diagram showing radio sending packet to other radio](./media/sending_step2.png?raw=true)

Finally, all the other devices connected via Bluetooth will be notified of the state change on TX and, hence, receive the packet data.

![Diagram showing radios sending packet to all connected phones](./media/sending_step3.png?raw=true)

And the message has been broadcast to everybody! Yippee!!!!

# Packet Format

Because messages of data can become quite large, messages are split into groups of packets that are all broadcasted. Each message or "group" will have its own unique ID, and each packet in the group includes the ID of the group it belongs to, the index of the packet (e.g. where it is in regards to the concatenated bytes of the final message), and the total amount of packets that belong in the group.
The packet can be **any binary data** that the clients want to send to each other.

#### Bluetooth LE Characteristic Value

| Length      | Data                            |
|-------------|---------------------------------|
| 4 bytes     | Group ID (big-endian)           |
| 1 byte      | Group Index                     |
| 1 byte      | Group Total                     |
| Remaining   | Data                            |

#### LoRa Radio Packets

The data sent over LoRa will have 4 bytes of data appended to the front to identify CLAW packets among other LoRa packets that may be picked up.

| Length      | Data                            |
|-------------|---------------------------------|
| 4 bytes     | 0x8248 (hex) for identification |
| 4 bytes     | Group ID (big-endian)           |
| 1 byte      | Group Index                     |
| 1 byte      | Group Total                     |
| Remaining   | Data                            |

# Bluetooth LE UUIDs

| Key               | UUID                                 | Allowed Operations |
|-------------------|--------------------------------------|--------------------|
| Primary Service   | 82480000-9a25-49fc-99be-2c16d1492d35 |                    |
| TX Characteristic | 82480001-9a25-49fc-99be-2c16d1492d35 | Notify             |
| RX Characteristic | 82480002-9a25-49fc-99be-2c16d1492d35 | Write              |

# Example Client

```js
async function connect() {

  const serviceUuid = parseInt('82480000-9a25-49fc-99be-2c16d1492d35');
  const txCharacteristicUuid = parseInt('82480001-9a25-49fc-99be-2c16d1492d35');
  const rxCharacteristicUuid = parseInt('82480002-9a25-49fc-99be-2c16d1492d35');

  try {
    console.log('Requesting Bluetooth Device...');
    const device = await navigator.bluetooth.requestDevice({
      filters: [
        {
          services: [serviceUuid]
        }
      ]
    });

    console.log('Connecting to GATT Server...');
    const server = await device.gatt.connect();

    console.log('Getting Service...');
    const service = await server.getPrimaryService(serviceUuid);

    console.log('Getting Characteristics...');
    const txCharacteristic = await service.getCharacteristic(txCharacteristicUuid);
    const rxCharacteristic = await service.getCharacteristic(rxCharacteristicUuid);

    console.log('Sending data...');
    rxCharacteristic.writeValue(new Uint8Array([0x01, 0x02, 0x03]));

    console.log('Enabling RX notifications...');
    txCharacteristic.startNotifications();
    txCharacteristic.addEventListener('characteristicvaluechanged', (event) => {
      const value = event.target.value;
      console.log('Received:', value);
    });
  } catch(error) {
    console.log('Uh oh... ' + error);
  }
}
```
