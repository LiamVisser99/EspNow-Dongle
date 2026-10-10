#include "Debug/Button.h"

void Button::init()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void Button::buton_hold(uint32_t time_Ms)
{
    button_time = time_Ms;
}

bool Button::button_loop()
{
    if ((delta_time = millis() - last_frame) >= BUTTON_POLLING_RATE_MS)
    {
        last_frame = millis();

        bool button_on = !digitalRead(BUTTON_PIN);

        if (!button_on && button_flag)
        {
            button_flag = false;
        }

        if (button_on)
        {
            polling += delta_time;
        }
        else
        {
            if (polling != 0)
                polling = 0;
        }

        if (polling >= button_time && button_time != 0)
        {
            button_flag = true;
            polling = 0;
            return true;
        }

        return false;
    }

    return false;
}