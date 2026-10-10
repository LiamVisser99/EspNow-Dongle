#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include "Wireless/ESPNow.h"

extern Preferences preferences;

class Storage
{
    public:
    esp_err_t check_mac_address();
    esp_err_t add_mac_address(const uint8_t *macAddress);
    esp_err_t allocate_mac_address();
    
    private:
};

extern Storage storage;