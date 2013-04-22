//==============================================================================
// Send.cpp
//==============================================================================
/*
    <description, licence, etc.>

    Assumes that Serial.begin has already been called.

    Packets include LRC checksum as last byte:
    http://en.wikipedia.org/wiki/Longitudinal_redundancy_check

    Date            Author            Notes
    dd/mm/yyyy        Seb Madgwick    Initial release
*/
//==============================================================================

//------------------------------------------------------------------------------
// Includes

#include "AHRS.h"
#include <Arduino.h>
#include "Calibration.h"
#include "FlexSensors.h"
#include "Send.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern AHRS ahrs;

//------------------------------------------------------------------------------
// Definitions

typedef union {
    int intVal;
    struct {
        char lsb;
        char msb;
    };
} IntUnion;

//------------------------------------------------------------------------------
// Functions - Public

void Send::flexSensorData() {
    char packet[64];
    int packetLength = 0;
    IntUnion intUnion;
    FlexSensors::read();    // read sensors before sending
    packet[packetLength++] = 'F';
    intUnion.intVal= (int)FlexSensors::channel[0];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[1];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[2];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[3];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[4];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)FlexSensors::channel[5];
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    packet[packetLength++] = calcChecksum(packet, packetLength);
    Serial.write((uint8_t*)packet, packetLength);
}

void Send::sensorData() {
    char packet[128];
    int packetLength = 0;
    IntUnion intUnion;
    packet[packetLength++] = 'S';
    intUnion.intVal= Calibration::gyrX;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::gyrY;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::gyrZ;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::accX;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::accY;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::accZ;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::magX;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::magY;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= Calibration::magZ;
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    packet[packetLength++] = calcChecksum(packet, packetLength);
    Serial.write((uint8_t*)packet, packetLength);
}

void Send::quaternionData() {
    char packet[64];
    int packetLength = 0;
    IntUnion intUnion;
    packet[packetLength++] = 'Q';
    intUnion.intVal= (int)(10000.0f * ahrs.q0);
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)(-10000.0f * ahrs.q1);    // negated complex elements for quaternion conjugate
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)(-10000.0f * ahrs.q2);
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    intUnion.intVal= (int)(-10000.0f * ahrs.q3);
    packet[packetLength++] = intUnion.msb;
    packet[packetLength++] = intUnion.lsb;
    packet[packetLength++] = calcChecksum(packet, packetLength);
    Serial.write((uint8_t*)packet, packetLength);
}

void Send::miscData(const char* const charArray) {
    char packet[64];
    int packetLength = 0;
    IntUnion intUnion;
    packet[packetLength++] = 'M';
    for(int i = 0; i < 8; i++) {
        packet[packetLength++] = charArray[i];
    }
    packet[packetLength++] = calcChecksum(packet, packetLength);
    Serial.write((uint8_t*)packet, packetLength);
}

//------------------------------------------------------------------------------
// Functions - Private

char Send::calcChecksum(const char* const packet, const int packetLength) {
    int i = 0;
    char checksum = 0;
    while(i < packetLength) {
        checksum ^= packet[i++];
    }
    return checksum;
}

//==============================================================================
// End of file
//==============================================================================