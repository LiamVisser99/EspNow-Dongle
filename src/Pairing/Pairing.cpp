#include "Pairing/Pairing.h"

void Pairing::begin_pairing_mode()
{
    pairing_flag = true;

    led.led_blink(1000, 60, CRGB::Purple);
    Serial.println("DISCONNECTED");
    pairing_mode = true;
}

void Pairing::cancle_pairing_mode()
{
    pairing_mode, pairing_flag, init_flag, time_flag = false;

    esp_now_del_peer(espNow.deafultMacAddress);
    espNow.set_peer(espNow.peripheralMacAddress);
}

void Pairing::pairing_mode_poller()
{
    if (pairing_mode)
    {
        if (!init_flag)
        {
            if (esp_now_is_peer_exist(espNow.peripheralMacAddress))
                esp_now_del_peer(espNow.peripheralMacAddress);
            espNow.set_peer(espNow.deafultMacAddress);
            init_flag = true;
        }

        if (!time_flag)
        {
            pairing_mode_timer_MS, pairing_mode_timer_S = millis();

            time_flag = true;
        }

        if (millis() - pairing_mode_timer_MS >= MACADDRESS_POLLING_RATE_MS)
        {
            pairing_mode_timer_MS = millis();
            
            wireless.send_discovery_packet();
        }

        if (millis() - pairing_mode_timer_S >= (MACADDRESS_POLLING_TIME_S * 1000))
        {
            cancle_pairing_mode();
        }
    }
}