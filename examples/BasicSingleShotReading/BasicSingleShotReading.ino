/*
 * BasicSingleEndedReading.ino
 * 
 * Demonstrates basic usage of the ADS111S library to read a single-ended
 * analog input from pin A0 of the ADS111x ADC.
 * 
 * Hardware Requirements:
 * - ADS111x ADC connected via I2C (SDA, SCL, GND, VCC)
 * - Analog input connected to A0 (e.g., a potentiometer or sensor)
 * 
 * Author: Saurav Sajeev
 */

 #include <ADS111S.h>

 // Create an ADS111S object with default configuration
 ADS111S adc;
 
 void setup() {
   // Start serial communication for debugging
   Serial.begin(115200);
   while (!Serial); // Wait for serial monitor to open (for some boards)
 
   // Initialize the ADC
   if (!adc.begin()) {
     Serial.println("Error: ADS111S ADC not detected!");
     while (1); // Halt if ADC is not found
   }
 
   Serial.println("ADS111S ADC initialized successfully.");
 }
 
 void loop() {
   // Read single-ended analog input from pin A0 (0)
   uint16_t value = adc.readFrom(0);
   
   // Print the raw ADC value
   Serial.print("A0 Value: ");
   Serial.println(value);
 
   // Optional: Calculate voltage based on gain (default gain assumed here)
   float voltage = (value / 32768.0) * 2.048; // Assuming 2.048V gain
   Serial.print("A0 Voltage: ");
   Serial.print(voltage, 3); // 3 decimal places
   Serial.println(" V");
 
   delay(1000); // Wait 1 second between readings
 }