#pragma once

#include <Arduino.h>
#include "Wireless/ESPNow.h"
#include "Storage/Packets.h"
#include "Debug/LED.h"
#include "Pairing/Pairing.h"

#define HEARTBEAT_POLLING_RATE_MS 500
#define BATTERY_POLLING_RATE_MS 5000

class Wireless
{
public:
    uint32_t start_frame_b = 0;
    uint32_t start_frame_h = 0;

    bool isActive = false;

    void init();

    esp_err_t send_haptic_packet();
    esp_err_t send_discovery_packet();
    esp_err_t send_heartbeat();

    void peripheral_heartbeat_poller();
    
private:


};

extern Wireless wireless;