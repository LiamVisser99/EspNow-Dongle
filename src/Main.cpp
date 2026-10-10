#include <Arduino.h>
#include "Wireless/Wireless.h"
#include "Serial/SerialProtocol.h"
#include "Wireless/ESPNow.h"
#include "Pairing/Pairing.h"
#include "Debug/LED.h"
#include "Debug/Button.h"

Preferences preferences;
Storage storage;
ESPNow espNow;
Wireless wireless;
Pairing pairing;
SerialProtocol serial;
LED led;
Button button;

bool pairing_flag = false;

void setup()
{
    Serial.begin(115200);

    espNow.init();

    led.init();

    button.init();

    button.buton_hold(2000);
}

void loop()
{
    wireless.peripheral_heartbeat_poller();

    pairing.pairing_mode_poller();

    serial.update();

    led.led_loop();

    bool button_on = button.button_loop();

    if (button_on && !pairing_flag)
    {
        pairing.begin_pairing_mode();
    }
    else if (button_on && pairing_flag)
    {
        pairing.cancle_pairing_mode();
    }
}