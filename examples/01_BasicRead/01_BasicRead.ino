// Example: Basic Read for I2Connect: AHT20
// Last Update: June 26, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Initializes the AHT20 sensor and reads basic temperature and humidity data 
// to the Serial Monitor.
//
// SKILLS LEARNED
// begin()
// readData()
// getTemperature()
// getHumidity()
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
    
    if (!aht20.begin(Wire, I2C_ADDRESS, I2C_CLOCK_HZ)) {
        Serial.println("AHT20 not detected. Please check your wiring!");
        while (1) { } // Halt execution
    }
    
    Serial.println("AHT20 detected and initialized.");
    Serial.println("--------------------------------");
}

void loop() {
    // readData() must be called to trigger a new measurement and update values
    if (aht20.readData()) {
        Serial.print("Temperature: ");
        Serial.print(aht20.getTemperature());
        Serial.print(" C  |  Humidity: ");
        Serial.print(aht20.getHumidity());
        Serial.println(" %");
    } else {
        Serial.println("Failed to read sensor data.");
    }
    
    delay(2000); // Wait 2 seconds between measurements
}
