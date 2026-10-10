#pragma once

#include <Arduino.h>
#include "Storage/Packets.h"
#include "Pairing/Pairing.h"
#include "Wireless/Wireless.h"

class SerialProtocol
{
public:
    bool read_packet(uint8_t* data, size_t size);
    void update();

private:
    uint8_t command = 0;
    uint8_t index = 0;
};

extern SerialProtocol serial;