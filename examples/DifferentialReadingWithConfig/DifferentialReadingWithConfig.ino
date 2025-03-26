/*
 * DifferentialReadingWithConfig.ino
 * 
 * Demonstrates advanced usage of the ADS111S library with a custom configuration.
 * Reads a differential analog input between A0 and A1, sets a specific gain,
 * data rate, and configures the comparator with thresholds.
 * 
 * Hardware Requirements:
 * - ADS111x ADC connected via I2C (SDA, SCL, GND, VCC)
 * - Analog inputs connected to A0 and A1 (e.g., a sensor with differential output)
 * 
 * Author: Saurav Sajeev
 */

 #include <ADS111S.h>

 // Define a custom configuration
 ADS111SCONFIG config = {
   .OS = ADS111S_OS_START_SINGLE,        // Start single-shot conversion
   .PGA = ADS111S_PGA_4_096V,            // Gain of 4.096V
   .MODE = ADS111S_MODE_SINGLE,          // Single-shot mode
   .DR = ADS111S_DR_128SPS,              // 128 samples per second
   .COMP_MODE = ADS111S_COMP_MODE_TRADITIONAL, // Traditional comparator mode
   .COMP_POL = ADS111S_COMP_POL_ACTIVE_HIGH,   // Active-high polarity
   .COMP_LAT = ADS111S_COMP_LAT_NON_LATCHING,  // Non-latching comparator
   .COMP_QUE = ADS111S_COMP_QUE_2_CONV         // Assert after 2 conversions
 };
 
 // Create an ADS111S object
 ADS111S adc;
 
 void setup() {
   // Start serial communication
   Serial.begin(115200);
   while (!Serial); // Wait for serial monitor to open (for some boards)
 
   // Initialize the ADC with the custom configuration
   if (!adc.begin(config)) {
     Serial.println("Error: ADS111S ADC not detected!");
     while (1); // Halt if ADC is not found
   }
 
   Serial.println("ADS111S ADC initialized with custom configuration.");
 
   // Set comparator thresholds (example values)
   adc.setThreshold(1000, 30000); // Low: 1000, High: 30000
   Serial.println("Comparator thresholds set: Low = 1000, High = 30000");
 }
 
 void loop() {
   // Read differential analog input between A0 and A1 (pin 0)
   uint16_t diffValue = adc.readFromDifferential(0);
   
   // Print the raw differential ADC value
   Serial.print("Differential A0-A1 Value: ");
   Serial.println(diffValue);
 
   // Calculate voltage based on the configured gain (4.096V)
   float voltage = (diffValue / 32768.0) * 4.096; // 4.096V full-scale range
   Serial.print("Differential Voltage: ");
   Serial.print(voltage, 3); // 3 decimal places
   Serial.println(" V");
 
   // Check the current gain in use
   float gainInUse = adc.getVoltageGainInUse();
   Serial.print("Current Gain: ");
   Serial.print(gainInUse, 3);
   Serial.println(" V");
 
   delay(2000); // Wait 2 seconds between readings
 }