#pragma once
#include <Arduino.h>

enum Command : uint8_t
{
    Motor_Command          = 1,
    Battery_Command        = 2,
    Discovery_Command      = 3,
    Pairing_Command        = 4,
    Cancle_Pairing_Command = 5,
    Confirm_Command        = 6
};

inline static uint8_t heartbeat_byte = 1;

struct __attribute__((packed)) HapticPacket
{
    uint8_t DataType = Motor_Command;

    uint16_t MotorIntensityB[20] = {};
    uint16_t MotorIntensityF[20] = {};

    uint16_t MotorDurationB[20] = {};
    uint16_t MotorDurationF[20] = {};
} inline static hapticData;

struct __attribute__((packed)) BatteryPacket
{
    uint8_t DataType = Battery_Command;

    float CellVoltage;
    uint8_t StateOfCharge;
    uint16_t TimeToFull;
} inline static batteryData;

struct __attribute__((packed)) DiscoveryPacket
{
    uint8_t DataType = Discovery_Command;
    uint8_t ProtocolVers = 1;

    uint8_t macAddress[6] = {};
}  inline static discoveryData;

struct __attribute__((packed)) ConfirmPacket
{
    uint8_t DataType = Confirm_Command;
    uint8_t ProtocolVers = 1;

    uint8_t macAddress[6] = {};
}   inline static confirmData;