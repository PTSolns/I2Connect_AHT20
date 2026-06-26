#include "PTSOLNS_I2CONNECT_AHT20.h"

PTSOLNS_I2CONNECT_AHT20::PTSOLNS_I2CONNECT_AHT20() {
    _wire = &Wire;
    _i2cAddress = DEFAULT_I2C_ADDRESS;
    _i2cClock = DEFAULT_I2C_CLOCK;
    _temperature = 0.0;
    _humidity = 0.0;
}

bool PTSOLNS_I2CONNECT_AHT20::begin(TwoWire &wirePort, uint8_t i2cAddress, uint32_t i2cClock) {
    _wire = &wirePort;
    setI2CAddress(i2cAddress); 
    _i2cClock = i2cClock;
    _wire->setClock(_i2cClock);

    delay(40); 

    if (!isConnected()) {
        return false;
    }

    if (!isCalibrated()) {
        if (!calibrate()) {
            return false;
        }
    }
    
    return true;
}

void PTSOLNS_I2CONNECT_AHT20::setI2CAddress(uint8_t i2cAddress) {
    _i2cAddress = i2cAddress;
}

void PTSOLNS_I2CONNECT_AHT20::setI2CClock(uint32_t i2cClock) {
    _i2cClock = i2cClock;
    if (_wire) {
        _wire->setClock(_i2cClock);
    }
}

bool PTSOLNS_I2CONNECT_AHT20::isConnected() {
    _wire->beginTransmission(_i2cAddress);
    return (_wire->endTransmission() == 0);
}

bool PTSOLNS_I2CONNECT_AHT20::softReset() {
    _wire->beginTransmission(_i2cAddress);
    _wire->write(AHT20_CMD_SOFTRESET);
    
    if (_wire->endTransmission() != 0) {
        return false;
    }
    
    delay(20); 
    return true;
}

bool PTSOLNS_I2CONNECT_AHT20::calibrate() {
    _wire->beginTransmission(_i2cAddress);
    _wire->write(AHT20_CMD_CALIBRATE);
    _wire->write(0x08);
    _wire->write(0x00);
    
    if (_wire->endTransmission() != 0) {
        return false;
    }
    
    delay(10);
    return isCalibrated();
}

uint8_t PTSOLNS_I2CONNECT_AHT20::readStatus() {
    _wire->requestFrom(_i2cAddress, (uint8_t)1);
    
    if (_wire->available()) {
        return _wire->read();
    }
    
    return 0;
}

bool PTSOLNS_I2CONNECT_AHT20::isCalibrated() {
    return (readStatus() & AHT20_STATUS_CALIBRATED) != 0;
}

bool PTSOLNS_I2CONNECT_AHT20::isBusy() {
    return (readStatus() & AHT20_STATUS_BUSY) != 0;
}

bool PTSOLNS_I2CONNECT_AHT20::triggerMeasurement() {
    _wire->beginTransmission(_i2cAddress);
    _wire->write(AHT20_CMD_MEASURE);
    _wire->write(0x33);
    _wire->write(0x00);
    return (_wire->endTransmission() == 0);
}

bool PTSOLNS_I2CONNECT_AHT20::readData() {
    if (!triggerMeasurement()) {
        return false;
    }

   
    unsigned long startTime = millis();
    while (isBusy()) {
        if (millis() - startTime > 100) {
            return false; // Timeout
        }
        delay(5);
    }

    uint8_t received = _wire->requestFrom(_i2cAddress, (uint8_t)6);
    
    if (received != 6) {
        return false;
    }

    uint8_t data[6];
    for (uint8_t i = 0; i < 6; i++) {
        data[i] = _wire->read();
    }

    
    if ((data[0] & AHT20_STATUS_BUSY) != 0) {
        return false;
    }

    
    uint32_t rawHumidity = data[1];
    rawHumidity <<= 8;
    rawHumidity |= data[2];
    rawHumidity <<= 4;
    rawHumidity |= (data[3] >> 4);
    
    _humidity = ((float)rawHumidity * 100.0) / 1048576.0;

    
    uint32_t rawTemp = (data[3] & 0x0F);
    rawTemp <<= 8;
    rawTemp |= data[4];
    rawTemp <<= 8;
    rawTemp |= data[5];
    
    _temperature = (((float)rawTemp * 200.0) / 1048576.0) - 50.0;

    return true;
}

float PTSOLNS_I2CONNECT_AHT20::getTemperature() const {
    return _temperature;
}

float PTSOLNS_I2CONNECT_AHT20::getHumidity() const {
    return _humidity;
}