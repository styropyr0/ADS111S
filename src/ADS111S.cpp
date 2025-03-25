#include "ADS111S.h"
#include <SensorHubTemplates.h>

ADS111S::ADS111S() : sensorHub(ADS111S_I2C_ADDR) {}

bool ADS111S::begin()
{
    config.OS = ADS111S_OS_START_SINGLE;
    config.PGA = ADS111S_PGA_4_096V;
    config.MODE = ADS111S_MODE_CONTINUOUS;
    config.DR = ADS111S_DR_128SPS;
    config.COMP_MODE = ADS111S_COMP_MODE_TRADITIONAL;
    config.COMP_POL = ADS111S_COMP_POL_ACTIVE_LOW;
    config.COMP_LAT = ADS111S_COMP_LAT_NON_LATCHING;
    config.COMP_QUE = ADS111S_COMP_QUE_1_CONV;

    return setConfig();
}

bool ADS111S::begin(ADS111SCONFIG config)
{
    this->config = config;
    return setConfig();
}

bool ADS111S::setConfig()
{
    if (!isConnected())
        return false;
    uint16_t cfg = (config.OS << 15) | (muxMode << 12) | (config.PGA << 9) | (config.MODE << 8) |
                   (config.DR << 5) | (config.COMP_MODE << 4) | (config.COMP_POL << 3) | (config.COMP_LAT << 2) | config.COMP_QUE;

    sensorHub.i2c_execute_16bit(ADS111S_CONFIG_REG, cfg);
    return true;
}

void ADS111S::setPin(uint8_t pin, bool differential)
{
    if (differential)
    {
        switch (pin)
        {
        case 0:
            muxMode = ADS111S_MUX_DIFF_0_1;
            break;
        case 1:
            muxMode = ADS111S_MUX_DIFF_0_3;
            break;
        case 2:
            muxMode = ADS111S_MUX_DIFF_1_3;
            break;
        case 3:
            muxMode = ADS111S_MUX_DIFF_2_3;
            break;
        default:
            muxMode = ADS111S_MUX_DIFF_0_1;
            break;
        }
    }
    else
    {
        switch (pin)
        {
        case 0:
            muxMode = ADS111S_MUX_SINGLE_0;
            break;
        case 1:
            muxMode = ADS111S_MUX_SINGLE_1;
            break;
        case 2:
            muxMode = ADS111S_MUX_SINGLE_2;
            break;
        case 3:
            muxMode = ADS111S_MUX_SINGLE_3;
            break;
        default:
            muxMode = ADS111S_MUX_SINGLE_0;
            break;
        }
    }

    setConfig();
}

uint16_t ADS111S::readFrom(uint8_t pin)
{
    uint16_t data = 0;
    setPin(pin, false);
    delay(50);
    sensorHub.i2c_read_Xbit(ADS111S_CONV_REG, &data, 16);
    return data;
}

uint16_t ADS111S::readFromDifferential(uint8_t pin)
{
    uint16_t data = 0;
    setPin(pin, true);
    delay(50);
    sensorHub.i2c_read_Xbit(ADS111S_CONV_REG, &data, 16);
    return data;
}

bool ADS111S::isConnected()
{
    return sensorHub.is_sensor_connected();
}

void ADS111S::setDataRate(uint8_t dataRate)
{
    if (dataRate > ADS111S_DR_860SPS)
        return;
    config.DR = dataRate;
    setConfig();
}

void ADS111S::setComparatorMode(bool mode)
{
    config.COMP_MODE = mode;
    setConfig();
}

void ADS111S::setComparatorPolarity(bool polarity)
{
    config.COMP_POL = polarity;
    setConfig();
}

void ADS111S::setComparatorLatching(bool latching)
{
    config.COMP_LAT = latching;
    setConfig();
}

void ADS111S::setComparatorQueue(uint8_t queue)
{
    if (queue > ADS111S_COMP_QUE_4_CONV)
        return;
    config.COMP_QUE = queue;
    setConfig();
}

void ADS111S::setGain(uint8_t gain)
{
    if (gain > ADS111S_PGA_0_256V)
        return;
    config.PGA = gain;
    setConfig();
}

void ADS111S::setMode(uint8_t mode)
{
    if (mode > ADS111S_MODE_SINGLE)
        return;
    config.MODE = mode;
    setConfig();
}

void ADS111S::setThreshold(uint16_t low, uint16_t high)
{
    sensorHub.i2c_execute_16bit(ADS111S_LO_THRESH_REG, low);
    sensorHub.i2c_execute_16bit(ADS111S_HI_THRESH_REG, high);
}

float ADS111S::getVoltageGainInUse()
{
    switch (config.PGA)
    {
    case ADS111S_PGA_0_256V:
        return 0.256;
    case ADS111S_PGA_0_512V:
        return 0.512;
    case ADS111S_PGA_1_024V:
        return 1.024;
    case ADS111S_PGA_2_048V:
        return 2.048;
    case ADS111S_PGA_4_096V:
        return 4.096;
    case ADS111S_PGA_6_144V:
        return 6.144;
    default:
        return 0.0;
    }
}