#ifndef PTSOLNS_I2CONNECT_AHT20_H
#define PTSOLNS_I2CONNECT_AHT20_H

#include <Arduino.h>
#include <Wire.h>

class PTSOLNS_I2CONNECT_AHT20 {
public:
    static const uint8_t DEFAULT_I2C_ADDRESS = 0x38;
    static const uint32_t DEFAULT_I2C_CLOCK = 100000UL;
    
    
    static const uint8_t AHT20_CMD_CALIBRATE = 0xBE;
    static const uint8_t AHT20_CMD_MEASURE = 0xAC;
    static const uint8_t AHT20_CMD_SOFTRESET = 0xBA;
    
    
    static const uint8_t AHT20_STATUS_BUSY = 0x80;
    static const uint8_t AHT20_STATUS_CALIBRATED = 0x08;

    PTSOLNS_I2CONNECT_AHT20();

    bool begin(TwoWire &wirePort = Wire, uint8_t i2cAddress = DEFAULT_I2C_ADDRESS, uint32_t i2cClock = DEFAULT_I2C_CLOCK);

    void setI2CAddress(uint8_t i2cAddress);
    void setI2CClock(uint32_t i2cClock);

    bool isConnected();
    bool softReset();
    bool calibrate();
    bool isCalibrated();
    bool isBusy();

    bool triggerMeasurement();
    bool readData();

    float getTemperature() const;
    float getHumidity() const;

private:
    TwoWire *_wire;
    uint8_t _i2cAddress;
    uint32_t _i2cClock;

    float _temperature;
    float _humidity;

    uint8_t readStatus();
};

#endif