// Example: LCD Display for I2Connect: AHT20
// Last Update: June 26, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Reads environmental data from the AHT20 and displays it on a standard 
// 16x2 character LCD sharing the same I2C bus.
// 
// Requires the "LiquidCrystal I2C" library to be installed.
//
// SKILLS LEARNED
// Interacting with multiple I2C devices on the same bus.
// Formatting float data for a character LCD.
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
#include <LiquidCrystal_I2C.h>

// User Settings
const uint32_t I2C_CLOCK_HZ    = 100000; // I2C clock speed. Keep at 100 kHz most of the time.
const uint8_t  AHT20_ADDRESS   = 0x38;   // Fixed address for the AHT20 sensor
const uint8_t  LCD_ADDRESS     = 0x27;   // Typical address for a 16x2 I2C LCD

PTSOLNS_I2CONNECT_AHT20 aht20;
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setup() {
    Wire.begin();
    
    // Set up the LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("PTSolns AHT20");
    
    // Set up the AHT20
    if (!aht20.begin(Wire, AHT20_ADDRESS, I2C_CLOCK_HZ)) {
        lcd.setCursor(0, 1);
        lcd.print("Sensor Error! ");
        while (1) { } // Halt execution
    }
    
    lcd.setCursor(0, 1);
    lcd.print("Initialized...");
    delay(2000);
    lcd.clear();
}

void loop() {
    if (aht20.readData()) {
        // Print Temperature on the top row
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(aht20.getTemperature(), 1); // Restrict to 1 decimal place
        lcd.print(" C   "); // Trailing spaces to clear leftover characters
        
        // Print Humidity on the bottom row
        lcd.setCursor(0, 1);
        lcd.print("Hum:  ");
        lcd.print(aht20.getHumidity(), 1); 
        lcd.print(" %   ");
    } else {
        lcd.setCursor(0, 0);
        lcd.print("Read Error!     ");
    }
    
    delay(2000);
}
