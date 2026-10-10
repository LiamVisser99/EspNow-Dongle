#include "Wireless/ESPNow.h"

void ESPNow::init()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        Serial.print("Failed To Initalise ESP Now!");
        return;
    }

    esp_wifi_set_max_tx_power(72);

    delay(20);

    if (esp_now_register_recv_cb(esp_now_recv_cb_t(onDataRecv)) != ESP_OK)
    {
        Serial.print("Failed To Initalise Callback!");
        return;
    }

    if (esp_now_register_send_cb(esp_now_send_cb_t(onDataSent)) != ESP_OK)
    {
        Serial.print("Failed To Initalise Callback!");
        return;
    }

    if (storage.check_mac_address() != ESP_OK)
    {
        Serial.println("No device detected, please add one.");
    }

    storage.allocate_mac_address();

    set_peer(peripheralMacAddress);
}

void ESPNow::get_mac_address()
{
    Serial.println(WiFi.macAddress());
}

void ESPNow::set_peer(const uint8_t *macAddress)
{
    memcpy(peerInfo.peer_addr, macAddress, 6);
    peerInfo.channel = 1;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);
}

void ESPNow::new_peer_confirmed()
{
    pairing.cancle_pairing_mode();
    delay(100);

    if (esp_now_is_peer_exist(espNow.peripheralMacAddress))
        esp_now_del_peer(peripheralMacAddress);
    set_peer(confirmData.macAddress);
    storage.add_mac_address(confirmData.macAddress);

    led.led_blink(500, 2, CRGB::RoyalBlue);
    Serial.println("PAIRED");

    delay(1000);
    ESP.restart();
}

void ESPNow::onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    if (len < 1)
        return;

    switch (incomingData[0])
    {
    case Motor_Command:
        if (len >= sizeof(hapticData))
            memcpy(&hapticData, incomingData, sizeof(hapticData));
        break;

    case Battery_Command:
        if (len >= sizeof(batteryData))
            memcpy(&batteryData, incomingData, sizeof(batteryData));
        break;

    case Confirm_Command:
        if (len >= sizeof(confirmData) && incomingData[1] == CURRENT_PROTOCOL_VERS)
            memcpy(&confirmData, incomingData, sizeof(confirmData));
        new_peer_confirmed();
        break;

    default:
        break;
    }
}

void ESPNow::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    packetAcked = (status == ESP_NOW_SEND_SUCCESS) ? true : false;
}