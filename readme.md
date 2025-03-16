# ADS111S Arduino Library

The **ADS111S** library provides an easy-to-use interface for interacting with the ADS111x series 16-bit Analog-to-Digital Converters (ADCs) over I2C. This library supports single-ended and differential analog input readings, configurable gain, data rate, operating mode, and comparator settings. It is designed to work seamlessly with the Arduino platform.

## Features
- Read single-ended or differential analog inputs.
- Configure programmable gain amplifier (PGA) settings (e.g., 6.144V, 4.096V, etc.).
- Set data rates from 8 SPS to 860 SPS.
- Control operating modes (continuous or single-shot).
- Configure the built-in comparator with threshold values, polarity, and latching options.
- Check sensor connectivity over I2C.

## Installation

### Using the Arduino Library Manager
1. Open the Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries**.
3. Search for `ADS111S`.
4. Click **Install** to download and install the library.

### Manual Installation
1. Download the latest release of this repository as a ZIP file.
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library**.
3. Select the downloaded ZIP file and click **Open**.
4. The library will be installed and ready to use.

### Dependencies
- **Arduino.h**: Core Arduino library (included with the Arduino IDE).
- **SensorHub.h**: A custom library for I2C communication (ensure it’s installed or included in your project).

## Usage

### Basic Example
```cpp
#include <ADS111S.h>

ADS111S adc; // Create an ADS111S object with default configuration

void setup() {
  Serial.begin(115200);
  
  // Initialize the ADC
  if (!adc.begin()) {
    Serial.println("Failed to detect ADS111S ADC!");
    while (1);
  }
  
  Serial.println("ADS111S ADC initialized successfully.");
}

void loop() {
  // Read single-ended analog input from pin A0
  uint16_t value = adc.readFrom(0);
  Serial.print("Analog Value (A0): ");
  Serial.println(value);
  
  delay(1000); // Wait 1 second
}
```

### Custom Configuration Example
```cpp
#include <ADS111S.h>

ADS111SCONFIG config = {
  .OS = ADS111S_OS_START_SINGLE,        // Single-shot mode
  .PGA = ADS111S_PGA_2_048V,            // Gain of 2.048V
  .MODE = ADS111S_MODE_SINGLE,          // Single-shot mode
  .DR = ADS111S_DR_128SPS,              // 128 samples per second
  .COMP_MODE = ADS111S_COMP_MODE_TRADITIONAL, // Traditional comparator
  .COMP_POL = ADS111S_COMP_POL_ACTIVE_LOW,    // Active-low polarity
  .COMP_LAT = ADS111S_COMP_LAT_NON_LATCHING,  // Non-latching
  .COMP_QUE = ADS111S_COMP_QUE_DISABLE        // Disable comparator queue
};

ADS111S adc(config); // Create an ADS111S object with custom configuration

void setup() {
  Serial.begin(115200);
  
  if (!adc.begin()) {
    Serial.println("Failed to detect ADS111S ADC!");
    while (1);
  }
  
  Serial.println("ADS111S ADC initialized with custom config.");
}

void loop() {
  // Read differential input between A0 and A1
  uint16_t diffValue = adc.readFromDifferential(0);
  Serial.print("Differential Value (A0-A1): ");
  Serial.println(diffValue);
  
  delay(1000);
}
```

## API Reference

### Constructor
- `ADS111S()`: Creates an ADS111S object with default configuration.
- `ADS111S(ADS111SCONFIG config)`: Creates an ADS111S object with a custom configuration.

### Methods
- `bool begin()`: Initializes the ADC with the default configuration. Returns `true` if successful.
- `bool begin(ADS111SCONFIG config)`: Initializes the ADC with a custom configuration. Returns `true` if successful.
- `uint16_t readFrom(uint8_t pin)`: Reads a single-ended analog input from the specified pin (0-3).
- `uint16_t readFromDifferential(uint8_t pin)`: Reads a differential analog input from the specified pin pair (0-3).
- `bool isConnected()`: Checks if the ADC is detected over I2C.
- `void setDataRate(uint8_t dataRate)`: Sets the data rate (e.g., `ADS111S_DR_128SPS`).
- `void setGain(uint8_t gain)`: Sets the PGA gain (e.g., `ADS111S_PGA_2_048V`).
- `void setMode(uint8_t mode)`: Sets the operating mode (e.g., `ADS111S_MODE_SINGLE`).
- `void setComparatorMode(bool mode)`: Sets the comparator mode (traditional or window).
- `void setComparatorPolarity(bool polarity)`: Sets the comparator polarity (active-low or active-high).
- `void setComparatorLatching(bool latching)`: Enables or disables comparator latching.
- `void setComparatorQueue(uint8_t queue)`: Sets the comparator queue behavior.
- `void setThreshold(uint16_t low, uint16_t high)`: Sets the low and high threshold values for the comparator.
- `float getVoltageGainInUse()`: Returns the current voltage gain in use.

### Configuration Structure
The `ADS111SCONFIG` struct allows customization of the ADC settings:
- `OS`: Operational status (e.g., `ADS111S_OS_START_SINGLE`).
- `PGA`: Programmable gain amplifier setting (e.g., `ADS111S_PGA_2_048V`).
- `MODE`: Operating mode (e.g., `ADS111S_MODE_SINGLE`).
- `DR`: Data rate (e.g., `ADS111S_DR_128SPS`).
- `COMP_MODE`: Comparator mode (e.g., `ADS111S_COMP_MODE_TRADITIONAL`).
- `COMP_POL`: Comparator polarity (e.g., `ADS111S_COMP_POL_ACTIVE_LOW`).
- `COMP_LAT`: Comparator latching (e.g., `ADS111S_COMP_LAT_NON_LATCHING`).
- `COMP_QUE`: Comparator queue (e.g., `ADS111S_COMP_QUE_DISABLE`).

### Predefined Constants
Constants for configuration are defined in `ADS111SDEFS.h`. Examples include:
- Gain options: `ADS111S_PGA_6_144V`, `ADS111S_PGA_4_096V`, etc.
- Data rates: `ADS111S_DR_8SPS`, `ADS111S_DR_860SPS`, etc.
- I2C address: `ADS111S_I2C_ADDR` (default: `0x48`).

## Hardware Requirements
- Compatible with ADS111x series ADCs (e.g., ADS1113, ADS1114, ADS1115).
- I2C interface (connect SDA and SCL to your Arduino’s I2C pins).
- Power supply: 2.0V to 5.5V (check your specific ADS111x model).

## License
This library is released under the [MIT License](LICENSE). Feel free to use, modify, and distribute it as needed.

## Author
- **Saurav Sajeev**

## Contributing
Contributions are welcome! Please submit a pull request or open an issue on the [GitHub repository](https://github.com/styropyr0/ADS111S) for suggestions, bug reports, or improvements.

