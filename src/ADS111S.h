#ifndef ADS111S_H
#define ADS111S_H

#include <Arduino.h>
#include <SensorHub.h>
#include <SensorHubTemplates.h>
#include "ADS111SDEFS.h"

#ifdef __cplusplus

/**
 * @struct ADS111SCONFIG
 * @brief Configuration structure for the ADS111S.
 */
typedef struct
{
    uint16_t OS;
    uint16_t PGA;
    uint16_t MODE;
    uint16_t DR;
    uint16_t COMP_MODE;
    uint16_t COMP_POL;
    uint16_t COMP_LAT;
    uint16_t COMP_QUE;
} ADS111SCONFIG;

/**
 * @class ADS111S
 * @brief Driver for the ADS111 Series 16-bit ADC.
 *
 * The ADS111S class enables communication with the ADS111 Series 16-bit ADC
 * over I2C. It provides methods to read single-ended and differential
 * analog inputs, set the data rate, gain, and operating mode, and configure
 * the comparator.
 *
 * @author Saurav Sajeev
 */
class ADS111S
{
public:
    /**
     * @brief Constructs an ADS111S object with the default configuration.
     */
    ADS111S();

    /**
     * @brief Constructs an ADS111S object with the specified configuration.
     * @param config The configuration to set.
     * @returns True if the ADC module is detected, false otherwise.
     */
    bool begin();

    /**
     * @brief Constructs an ADS111S object with the specified configuration.
     * @param config The configuration to set.
     * @returns True if the ADC module is detected, false otherwise.
     */
    bool begin(ADS111SCONFIG config);

    /**
     * @brief Reads a differential analog input from the specified pins.
     * @param pin The pin to read from (0-3).
     * @returns The analog input value.
     */
    uint16_t readFrom(uint8_t pin);

    /**
     * @brief Reads a differential analog input from the specified pins.
     * @param pin The pin to read from (0-3).
     * @returns The analog input value.
     */
    uint16_t readFromDifferential(uint8_t pin);

    /**
     * @brief Checks if the sensor is connected over I2C.
     * @returns True if the sensor is detected, false otherwise.
     */
    bool isConnected();

    /**
     * @brief Sets the data rate.
     * @param dataRate The data rate to set.
     */
    void setDataRate(uint8_t dataRate);

    /**
     * @brief Sets the comparator mode.
     * @param mode The mode to set.
     */
    void setComparatorMode(bool mode);

    /**
     * @brief Sets the comparator polarity.
     * @param polarity The polarity to set.
     */
    void setComparatorPolarity(bool polarity);

    /**
     * @brief Sets the comparator latching.
     * @param latching The latching to set.
     */
    void setComparatorLatching(bool latching);

    /**
     * @brief Sets the comparator queue.
     * @param queue The queue to set.
     */
    void setComparatorQueue(uint8_t queue);

    /**
     * @brief Sets the gain.
     * @param gain The gain to set.
     */
    void setGain(uint8_t gain);

    /**
     * @brief Sets the operating mode.
     * @param mode The mode to set.
     */
    void setMode(uint8_t mode);

    /**
     * @brief Sets the threshold values for the comparator.
     * @param low The low threshold value.
     * @param high The high threshold value.
     */
    void setThreshold(uint16_t low, uint16_t high);

    /**
     * @brief Gets the voltage gain in use.
     * @returns The voltage gain.
     */
    float getVoltageGainInUse();

private:
    ADS111SCONFIG config;
    SensorHub sensorHub;
    uint8_t muxMode = ADS111S_MUX_SINGLE_0;

    bool setConfig();
    void setPin(uint8_t pin, bool differential);
};

#endif // __cplusplus
#endif // ADS111S_H