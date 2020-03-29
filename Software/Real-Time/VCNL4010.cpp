#include <iostream>
#include "VCNL4010.h"
#include "wiringPiI2C.h"

using namespace std;

void VCNL4010::VCNL4010config(int fd_VCNL4010, int samplingRate)
{
    /** Sets sampling rate and enables VCNL4010 ALS interrupt **/
    // VCNL4010 init
    wiringPiI2CWriteReg8(fd_VCNL4010, VCNL4010_COMMAND, 0); // reset the StateMachine
    wiringPiI2CWriteReg8(fd_VCNL4010, VCNL4010_AMBIENTPARAMETER, samplingRate << 4 | 0xD);
    wiringPiI2CWriteReg8(fd_VCNL4010, VCNL4010_PROXRATE, samplingRate);
    // Set Interrupt
    wiringPiI2CWriteReg8(fd_VCNL4010, VCNL4010_INTCONTROL, 0x04);              // Enable Interrupt [AMBIENT]
    wiringPiI2CWriteReg8(fd_VCNL4010, VCNL4010_COMMAND, VCNL4010_MEASUREBOTH); // Start Measurement
}

float VCNL4010::getAmbient(int fd_VCNL4010)
{
    uint16_t raw = (wiringPiI2CReadReg8(fd_VCNL4010, VCNL4010_AMBIENTDATA) << 8 | wiringPiI2CReadReg8(fd_VCNL4010, VCNL4010_AMBIENTDATA + 1));
    float lux = ((16000 - 0.25) / 65536) * (float)raw + 0.25;
    return lux;
}

float VCNL4010::getProximity(int fd_VCNL4010)
{
    uint16_t raw = (wiringPiI2CReadReg8(fd_VCNL4010, VCNL4010_PROXIMITYDATA) << 8 | wiringPiI2CReadReg8(fd_VCNL4010, VCNL4010_PROXIMITYDATA + 1));
    return raw * (-1) * (1 / 315.18) + 208;
}