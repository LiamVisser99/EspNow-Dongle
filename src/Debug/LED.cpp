#include "Debug/LED.h"

void LED::init()
{
    FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(leds, 1);
    FastLED.setBrightness(100);
}

void LED::led_loop()
{
    if (millis() - last_frame >= current_time_between_MS)
    {
        last_frame = millis();
        if (current_count != 0)
        {
            if (!led_on)
            {
                set_led_color(current_color);
                led_on = true;
            }
            else
            {
                set_led_color(CRGB::Black);
                led_on = false;
                current_count--;
            }
        }
    }
}

void LED::set_led_color(const CRGB &color)
{
    leds[0] = color;
    FastLED.show();
}

void LED::led_blink(uint32_t time_between_MS, uint8_t count, const CRGB &color)
{
    current_count = count;
    current_time_between_MS = time_between_MS;
    current_color = color;

    last_frame = millis() - time_between_MS;
}