#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include "Storage/Packets.h"
#include "Storage/Storage.h"
#include "Wireless/Wireless.h"
#include "Pairing/Pairing.h"
#include "Debug/LED.h"

#define CURRENT_PROTOCOL_VERS 1

class ESPNow
{
public:
    void init();

    void get_mac_address();

    inline static void set_peer(const uint8_t *macAddress);
    inline static void new_peer_confirmed();

    inline static bool packetAcked = false;

    uint8_t deafultMacAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    inline static uint8_t peripheralMacAddress[6] = {0};

    inline static bool tempp = false;

    //uint8_t peripheralMacAddress[6] = {0xD8, 0x3B, 0xDA, 0x89, 0x43, 0x00}; <- Vest

private:
    inline static esp_now_peer_info_t peerInfo{};

    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
    static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
};

extern ESPNow espNow;