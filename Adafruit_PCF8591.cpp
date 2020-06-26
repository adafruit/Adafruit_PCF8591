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
Adafruit_PCF8591::Adafruit_PCF8591(void) {}

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

/**
 * Enables the DAC output or sets it to tri-state / high-Z
 *
 * @param enable Flag for desired DAC state
 */
void Adafruit_PCF8591::enableDAC(bool enable) {
  _dacenable = enable;
  this->analogWrite(_dacval);
}

/**
 * Writes a uint8_t value to the DAC output
 *
 * @param output The value to write: 0 is GND and 255 is VCC
 */
void Adafruit_PCF8591::analogWrite(uint8_t output) {
  uint8_t buffer[2] = {0, 0};
  if (_dacenable) {
    buffer[0] = PCF8591_ENABLE_DAC;
    buffer[1] = output;
  }
  _dacval = output;
  i2c_dev->write(buffer, 2);
}

/**
 * Read an analog value from one of the four ADC inputs
 *
 * @param adcnum The single-ended ADC to read from, 0 thru 3
 * @return The value read: 0 is GND and 255 is VCC
 */
uint8_t Adafruit_PCF8591::analogRead(uint8_t adcnum) {
  _halfRead(adcnum);        // trigger the measurement
  return _halfRead(adcnum); // read the result
}

/**
 * Reads then writes from the PCF8591. Must be called twice
 * with the same arguments to receive the correct reading.
 *
 * The result from the measurement triggered by the first write
 * isn't returned until the second read.
 *
 * See section 8.4 "A/D Conversion" in the datasheet for more info:
 * https://www.nxp.com/docs/en/data-sheet/PCF8591.pdf
 * @param adcnum The single-ended ADC to read from, 0 thru 3
 * @return The value read: 0 is GND and 255 is VCC
 */
uint8_t Adafruit_PCF8591::_halfRead(uint8_t adcnum) {
  // we'll reuse the same buffer
  uint8_t buffer[2] = {0, 0};

  if (_dacenable) {
    buffer[0] = PCF8591_ENABLE_DAC;
    buffer[1] = _dacval;
  }

  // adcnum cannot be larger than 3
  adcnum = min(adcnum, (uint8_t)3);
  buffer[0] |= (adcnum & 0x3);

  i2c_dev->write_then_read(buffer, 2, buffer, 2);
  return buffer[1];
}
