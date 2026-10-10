#pragma once

#include <Arduino.h>
#include "Wireless/ESPNow.h"
#include "Wireless/Wireless.h"

#define MACADDRESS_POLLING_RATE_MS 2000
#define MACADDRESS_POLLING_TIME_S 20

extern bool pairing_flag;

class Pairing
{
public:
    void begin_pairing_mode();
    void cancle_pairing_mode();
    void pairing_mode_poller();

    bool pairing_mode = false;

private:
    bool time_flag = false;
    bool init_flag = false;

    uint32_t pairing_mode_timer_MS = 0;
    uint32_t pairing_mode_timer_S = 0;
};

extern Pairing pairing;