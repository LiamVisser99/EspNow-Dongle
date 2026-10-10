#pragma once

#include <Arduino.h>
#include <Debug/LED.h>

#define BUTTON_PIN 0
#define BUTTON_POLLING_RATE_MS 50

class Button
{
public:
    void init();
    bool button_loop();

    void buton_hold(uint32_t time_Ms);

private:
    uint32_t delta_time = 0;
    uint32_t button_time = 0;
    uint32_t last_frame = 0;
    uint32_t polling = 0;
    bool button_flag = false;
};