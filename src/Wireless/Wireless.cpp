#include "Wireless/Wireless.h"

esp_err_t Wireless::send_haptic_packet()
{
    return esp_now_send(espNow.peripheralMacAddress, (uint8_t *)&hapticData, sizeof(hapticData));
}


esp_err_t Wireless::send_discovery_packet()
{
    WiFi.macAddress(discoveryData.macAddress);
    return esp_now_send(espNow.deafultMacAddress, (uint8_t *)&discoveryData, sizeof(discoveryData));
}

esp_err_t Wireless::send_heartbeat()
{
    return esp_now_send(espNow.peripheralMacAddress, (uint8_t *)&heartbeat_byte, sizeof(heartbeat_byte));
}

void Wireless::peripheral_heartbeat_poller()
{
    if (millis() - start_frame_h >= HEARTBEAT_POLLING_RATE_MS)
    {

        start_frame_h = millis();

        send_heartbeat();

        if (espNow.packetAcked)
        {
            espNow.packetAcked = false;

            if (!isActive)
            {
                Serial.println("CONNECTED");
                if (!pairing.pairing_mode)
                    led.set_led_color(CRGB::Green);
            }

            isActive = true;
        }
        else if (!espNow.packetAcked)
        {

            if (isActive)
            {
                Serial.println("DISCONNECTED");
                if (!pairing.pairing_mode)
                    led.set_led_color(CRGB::Red);
            }

            isActive = false;
        }
    }
}