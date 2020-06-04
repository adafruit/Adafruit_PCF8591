/*!
 *  @file Adafruit_PCF8591.cpp
 *
 *  @mainpage Adafruit PCF8591 Combo ADC + DAC
 *
 *  @section intro_sec Introduction
 *
 *  This is a library for the Adafruit PCF8591 Combo ADC + DAC
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
 *  @section author Author
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 *  @section license License
 *
 *  BSD license, all text above must be included in any redistribution
 */

#include "Adafruit_PCF8591.h"

/*!
 * @brief  PCF8591 constructor
 */
Adafruit_PCF8591::Adafruit_PCF8591(void) {
}

/**
 * Initialises the I2C bus, and finds the PCF8591 on the bus
 *
 * @param i2caddr   The I2C address to use for the sensor.
 * @param  *theWire Optional wire interface, defaults to &Wire
 * @return True if initialisation was successful, otherwise False.
 */
bool Adafruit_PCF8591::begin(uint8_t i2caddr, TwoWire *theWire) {
  if (i2c_dev) {
    delete i2c_dev; // remove old interface
  }

  i2c_dev = new Adafruit_I2CDevice(i2caddr, theWire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return true;
}
