#include <Wire.h>
#include <PTSolns_I2Connect_AHT20.h>
#include <PTSolns_I2Connect_OLED.h> 

// User Settings
const uint32_t I2C_CLOCK_HZ  = 100000; 
const uint8_t  AHT20_ADDRESS = 0x38;   
const uint8_t  OLED_ADDRESS  = 0x3C;   

PTSolns_I2Connect_AHT20 aht20; 
PTSolns_I2Connect_OLED oled; 

void setup() {
    Wire.begin();
    
    oled.begin(Wire, OLED_ADDRESS, I2C_CLOCK_HZ); 
    oled.clearDisplay(); 
    
    oled.setCursor(0, 0);
    oled.print("PTSolns AHT20");
    
    // CRITICAL: Push the buffer to the screen
    oled.display(); 
    
    if (!aht20.begin(Wire, AHT20_ADDRESS, I2C_CLOCK_HZ)) {
        oled.setCursor(0, 16); // Shifted down 16 pixels
        oled.print("Sensor Error! ");
        oled.display(); 
        while (1) { } 
    }
    
    oled.setCursor(0, 16);
    oled.print("Initialized...");
    oled.display(); 
    
    delay(2000);
}

void loop() {
    if (aht20.readData()) {
        // Clear the buffer before drawing the new frame
        oled.clearDisplay(); 
        
        // Top Row
        oled.setCursor(0, 0);
        oled.print("Temp: ");
        oled.print(aht20.getTemperature(), 1); 
        oled.print(" C"); 
        
        // Bottom Row
        oled.setCursor(0, 16); 
        oled.print("Hum:  ");
        oled.print(aht20.getHumidity(), 1); 
        oled.print(" %");
        
        // CRITICAL: Push the complete frame to the screen
        oled.display(); 
        
    } else {
        oled.clearDisplay();
        oled.setCursor(0, 0);
        oled.print("Read Error!");
        oled.display();
    }
    
    delay(2000); 
}
