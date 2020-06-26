/*!
 *  @file Adafruit_PCF8591.h
 *
 *  This is a library for the PCF8591 Combo ADC + DAC
 *
 *  Designed specifically to work with the Adafruit PCF8591 Breakout
 *  -----> https://www.adafruit.com/product/4648
 *
 *  These ADC/DACs use I2C to communicate, 2 pins are required to interface
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 *  BSD license, all text above must be included in any redistribution
 */

#ifndef ADAFRUIT_PCF8591_H
#define ADAFRUIT_PCF8591_H

#include "Arduino.h"
#include <Adafruit_I2CDevice.h>

#define PCF8591_DEFAULT_ADDR 0x48 /**< PCF8591 Default Address */
#define PCF8591_ENABLE_DAC 0x40   ///< control bit for having the DAC active
/**
 * Driver for the Adafruit PCF8591 Combo ADC + DAC
 */
class Adafruit_PCF8591 {
public:
  Adafruit_PCF8591(void);

  bool begin(uint8_t i2caddr = PCF8591_DEFAULT_ADDR, TwoWire *theWire = &Wire);
  void enableDAC(bool enable);
  uint8_t analogRead(uint8_t adcnum);
  void analogWrite(uint8_t output);

private:
  Adafruit_I2CDevice *i2c_dev = NULL; ///< Pointer to I2C bus interface
  uint8_t _dacval = 0;
  bool _dacenable = false;
  uint8_t _halfRead(uint8_t adcnum);
};

#endif
