#include "Storage/Storage.h"

esp_err_t Storage::check_mac_address()
{
    preferences.begin("Storage", false);
    bool temperr = preferences.isKey("mac_address");
    preferences.end();

    return (temperr == true) ? ESP_OK : ESP_FAIL;
}

esp_err_t Storage::add_mac_address(const uint8_t *macAddress)
{
    preferences.begin("Storage", false);
    size_t temperr = preferences.putBytes("mac_address", macAddress, 6);
    preferences.end();

    return (temperr == 6) ? ESP_OK : ESP_FAIL;
}

esp_err_t Storage::allocate_mac_address()
{
    preferences.begin("Storage", false);
    size_t temp_bytes = preferences.getBytes("mac_address", espNow.peripheralMacAddress, 6);
    preferences.end();

    return (temp_bytes == 6) ? ESP_OK : ESP_FAIL;
}