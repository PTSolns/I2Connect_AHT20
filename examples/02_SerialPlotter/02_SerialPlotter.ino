// Example: Serial Plotter for I2Connect: AHT20
// Last Update: June 26, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Outputs comma-separated variables (CSV) designed specifically to be viewed 
// in the Arduino IDE Serial Plotter. Go to Tools -> Serial Plotter to view 
// the live graph (ensure baud is set to 115200).
//
// SKILLS LEARNED
// Formatting data for the Arduino IDE Serial Plotter tool.
//
// DESCRIPTION
// The I2Connect: AHT20 is a compact temperature and humidity sensing module 
// based on the AHT20 digital sensor. It provides a simple and reliable way 
// to add environmental sensing capabilities to embedded systems.
// The module communicates over the standard I2C interface with a fixed address 
// of 0x38. If multiple AHT20 modules are required in the same system, an I2C 
// multiplexer must be used.
// Like all I2Connect modules, it features dual Qwiic compatible connectors for 
// easy daisy-chaining and an angled male header for breadboard use. It is 
// fully compatible with both 3.3V and 5V microcontroller systems.

#include <Wire.h>
#include <PTSOLNS_I2CONNECT_AHT20.h>

// User Settings
const uint32_t SERIAL_BAUD  = 115200; // Serial baud setting
const uint32_t I2C_CLOCK_HZ = 100000; // I2C clock speed. Keep at 100 kHz most of the time.
const uint8_t  I2C_ADDRESS  = 0x38;   // Fixed address for the AHT20 sensor

PTSOLNS_I2CONNECT_AHT20 aht20;

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial) { }

    Wire.begin();
    
    // Initialize without blocking serial prints to keep the plotter clean
    aht20.begin(Wire, I2C_ADDRESS, I2C_CLOCK_HZ);
    
    // Print the variable labels for the Serial Plotter legend
    Serial.println("Temperature_C,Humidity_%");
}

void loop() {
    if (aht20.readData()) {
        // Output format must be: Value1,Value2
        Serial.print(aht20.getTemperature());
        Serial.print(",");
        Serial.println(aht20.getHumidity());
    }
    
    delay(500); // Read faster for a smoother graph
}
