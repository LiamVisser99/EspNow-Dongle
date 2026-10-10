#include "Serial/SerialProtocol.h"

bool SerialProtocol::read_packet(uint8_t *data, size_t size)
{
    data[index++] = Serial.read();

    if (index == size)
    {
        index, command = 0;

        return true;
    }

    return false;
}

void SerialProtocol::update()
{
    while (Serial.available() > 0)
    {

        if (command == 0)
            command = Serial.peek();

        switch (command)
        {
        case Motor_Command:
        {
            if (read_packet((uint8_t *)&hapticData, sizeof(hapticData)))
                wireless.send_haptic_packet();

            break;
        }

        case Pairing_Command:
            pairing.begin_pairing_mode();
            break;

        case Cancle_Pairing_Command:
            pairing.cancle_pairing_mode();
            break;
            // Logic here
        default:
            Serial.read();
            index, command = 0;
            break;
        }
    }
}