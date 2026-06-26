# PTSolns *I2Connect: AHT20* Library

![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Sensor](https://img.shields.io/badge/Sensor-Temp_%26_Humidity-orange)

Library for the PTSolns *I2Connect: AHT20* module. Available through both the Arduino Library Manager and the PTSolns IDE Library Manager, this library provides simple access to the module's temperature and humidity measurements while automatically managing I2C communication and sensor calibration.

---

## Overview

The *I2Connect: AHT20* is a compact temperature and humidity sensing module based on the AHT20 digital sensor. Designed as part of the I2Connect Series, the module provides a simple and reliable way to add environmental sensing capabilities to embedded systems. 

The sensor communicates over the industry standard I2C interface and delivers temperature and relative humidity measurements with minimal software overhead. The module is compatible with both 3.3V and 5V systems, making it suitable for use with a wide range of popular microcontroller platforms. 

Like all I2Connect modules, it connects using dual Qwiic® compatible connectors to easily integrate into existing I2C systems without soldering, while the preinstalled right-angle header provides direct access to the I2C bus for breadboard-based prototyping.

---

## *I2Connect* Series

The PTSolns *I2Connect* Series is a family of plug and play expansion modules designed to simplify the integration of sensors, displays, user interfaces, and other peripherals into embedded systems. Built around the industry standard I2C communication protocol and featuring convenient Qwiic® compatible connectors (4 pin, 1 mm JST SH), *I2Connect* modules can be quickly connected without soldering or complex wiring.

Each module is fully assembled and includes a preinstalled male header that is compatible with standard solderless breadboards, enabling immediate use and rapid prototyping. Designed to work seamlessly with a wide range of microcontroller platforms, I2Connect modules combine compact hardware, comprehensive documentation, and easy to use software libraries. The _I2Connect_ Series enables makers, students, educators, and professionals to rapidly prototype, evaluate, and develop reliable electronic systems.

The following modules are part of the *I2Connect* Series:

* [**AHT20**](https://ptsolns.com/products/i2connect-aht20) — Temperature & Humidity
* [**VEML7700**](https://ptsolns.com/products/i2connect-veml7700) — Light & Lux
* [**EEPROM**](https://ptsolns.com/products/i2connect-eeprom) — 2 Mbit Memory
* **Buttons** — User Input via 4×4 Matrix of Buttons
* **Digit Display** — Dual 7 Segment Display
* **ICP-20100** — Pressure & Temperature
* **KXTJ3-1057** — 3 Axis Accelerometer
* **MUX** — 4 Channel I2C Multiplexer
* **OLED** — 0.96" 128×64 OLED Display
* **I2C Doctor** — I2C Bus Recovery and Diagnostics
* **...and more!**

---

## Key Features

* Highly accurate temperature and relative humidity sensing.
* Fixed I2C address of 0x38.
* 3.3V and 5V logic and power compatibility.
* Pre-calibrated digital output.
* PCB cutout surrounding the sensor for improved measurement accuracy.
* Dual Qwiic® compatible 4-pin JST SH connectors for daisy-chaining.
* Breadboard-friendly 4-pin 2.54mm angled male header.
* Integrated power LED with a physical disconnect pad on the rear.

---

## I2Connect Ecosystem

The *I2Connect: AHT20* is part of the PTSolns I2Connect ecosystem.

All *I2Connect* modules utilize a standardized 4 pin JST SH 1.0 mm connector carrying:

| Pin | Function |
| --- | -------- |
| 1   | GND      |
| 2   | VCC      |
| 3   | SDA      |
| 4   | SCL      |

This connector follows the widely adopted Qwiic® standard, allowing modules and compatible boards to be connected without soldering.

For maximum compatibility, the module also includes a preinstalled angled male header, allowing use with virtually any 3.3 V or 5 V microcontroller platform even when a Qwiic compatible connector is unavailable.

---

## AHT20 Specifications

| Parameter               | Value                          |
| ----------------------- | ------------------------------ |
| Sensor Type             | AHT20 Digital Sensor           |
| Measurement Output      | Temperature & Humidity         |
| Interface               | I2C                            |
| I2C Address             | 0x38 (Fixed)                   |
| Operating Voltage       | 3.3 V / 5 V Rated              |
| Communication Speed     | Standard (100 kHz)             |
| Dimensions              | 33.2 mm x 22.9 mm              |
| Connectors              | 2x 4-pin 1mm JST SH            |

---

## I2C Addressing & Multiplexing

The *I2Connect: AHT20* module uses a fixed I2C address of:

```text
0x38

---
This address cannot be modified. If multiple AHT20 modules are required in the same system, an I2C multiplexer must be used.

The PTSolns I2Connect: MUX module provides four independent I2C channels, allowing up to four AHT20 modules with the same fixed I2C address to be connected to a single microcontroller.

```text

