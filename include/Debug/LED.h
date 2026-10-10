#pragma once

#include <Arduino.h>
#include <FastLED.h>

#define LED_DI_PIN 40
#define LED_CI_PIN 39

class LED
{
public:
    void init();
    void led_loop();

    void set_led_color(const CRGB &color);
    void led_blink(uint32_t time_between_MS, uint8_t count, const CRGB &color);

private:
    uint32_t last_frame = 0;
    uint32_t current_time_between_MS = 0;
    uint8_t current_count = 0;
    bool led_on = false;

    CRGB leds[1];
    CRGB current_color;
};

extern LED led;