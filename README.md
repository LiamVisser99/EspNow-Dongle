# ESP_Now Ultra Low Latency Dongle Designed for my Haptic Vest

Lightweight, bare-metal firmware designed for extreemly low latency haptic communication between a perepherial and client.

*Note: This system was designed, implemented, and written over a 4-day period while initially learning C++ and bare-metal constraints so some bugs may be present.*

## Designed for Ultra Low Latency

To guarantee minimal latency and low bandwith over ESP-Now, all network payloads are packed and small in size.

### Low Level Config

To bypass network wrappers and interract with the raw ESPIDF APIs, transceiver hardware is limited via esp_wifi_set_max_tx_power(72) to balance thermals and reliability *The dongle still gets warm*
Uses callbacks to process incoming info out-of-band.

#### Non-Blocking Hardware Interraction

To protect time-critical communication such as transmission and reciving (surprise, this is what a dongle does lol) non blocking timers with millis() are implemented to handle button and led logic.

##### Permanent storage (NVS) Integration and Dynamic Discovery

Allows for dynamic discovery and auto connection using NVS to remeber MAC adresses. When the client has no connection it brodcasts its MAC address on 0xFF band, when the pairing button is held down, the dongle scans for a time until it finds a device brodcasting on the oxFF band, runs some checks and connects (using NVS to sustain connection upon replug).

###### What I learned

This project taught me much about the structure used in wireless systems, struct managment, and low level systems.
