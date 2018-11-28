#include <Wire.h>

#include "MKRENV.h"

#define HTS221_ADDRESS   0x5F
#define LPS25H_ADDRESS   0x5C
#define VEML6075_ADDRESS 0x10

#define LIGHT_SENSOR_PIN A3

ENVClass::ENVClass(TwoWire  & wire, int lightSensorPin) :
  _wire(&wire),
  _lightSensorPin(lightSensorPin)
{
}

int ENVClass::begin()
{
  _wire->begin();

  if (i2cRead(HTS221_ADDRESS, 0x0f) != 0xbc) {
    end();

    return 0;
  }

  if (i2cRead(LPS25H_ADDRESS, 0x0f) != 0xbd) {
    end();

    return 0;
  }

  if (i2cReadWord(VEML6075_ADDRESS, 0x0c) != 0x0026) {
    end();

    return 0;
  }

  readHTS221Calibration();

  i2cWrite(HTS221_ADDRESS, 0x20, 0x80);
  i2cWrite(LPS25H_ADDRESS, 0x20, 0x80);
  i2cWriteWord(VEML6075_ADDRESS, 0x00, 0x0010);

  return 1;
}

void ENVClass::end()
{
  i2cWriteWord(VEML6075_ADDRESS, 0x00, 0x0001);
  i2cWrite(LPS25H_ADDRESS, 0x20, 0x00);
  i2cWrite(HTS221_ADDRESS, 0x20, 0x00);

  _wire->end();

  // restore the light sensor pin to input mode
  pinMode(LIGHT_SENSOR_PIN, INPUT);
}

float ENVClass::readTemperature()
{
  i2cWrite(HTS221_ADDRESS, 0x21, 0x01);

  while ((i2cRead(HTS221_ADDRESS, 0x27) & 0x02) == 0) {
    yield();
  }

  int16_t tout = i2cRead16(HTS221_ADDRESS, 0x2a);

  return (tout * _hts221TemperatureSlope + _hts221TemperatureZero);
}

float ENVClass::readHumidity()
{
  i2cWrite(HTS221_ADDRESS, 0x21, 0x01);

  while ((i2cRead(HTS221_ADDRESS, 0x27) & 0x02) == 0) {
    yield();
  }

  int16_t hout = i2cRead16(HTS221_ADDRESS, 0x28);

  return (hout * _hts221HumiditySlope + _hts221HumidityZero);
}

float ENVClass::readPressure()
{
  i2cWrite(LPS25H_ADDRESS, 0x21, 0x01);

  while ((i2cRead(LPS25H_ADDRESS, 0x27) & 0x02) == 0) {
    yield();
  }

  return (i2cRead(LPS25H_ADDRESS, 0x28) | (i2cRead(LPS25H_ADDRESS, 0x29) << 8) | (i2cRead(LPS25H_ADDRESS, 0x2a) << 16)) / 40960.0;
}

float ENVClass::readLux()
{
  float mV = (analogRead(_lightSensorPin) * 3300.0) / 1023.0;

  return (mV / 2.0);
}

float ENVClass::readUVA()
{
  uint16_t uva = i2cReadWord(VEML6075_ADDRESS, 0x07);
  uint16_t uvcomp1 = i2cReadWord(VEML6075_ADDRESS, 0x0a);
  uint16_t uvcomp2 = i2cReadWord(VEML6075_ADDRESS, 0x0b);

  float uvaComp = uva - (2.22 * uvcomp1) - (1.33 * uvcomp2);

  return uvaComp;
}

float ENVClass::readUVB()
{
  uint16_t uvb = i2cReadWord(VEML6075_ADDRESS, 0x09);
  uint16_t uvcomp1 = i2cReadWord(VEML6075_ADDRESS, 0x0a);
  uint16_t uvcomp2 = i2cReadWord(VEML6075_ADDRESS, 0x0b);

  float uvbComp = uvb - (2.95 * uvcomp1) - (1.74 * uvcomp2);

  return uvbComp;
}

float ENVClass::readUVIndex()
{
  float uva = readUVA();
  float uvb = readUVB();

  float uvi = ((uva * 0.001461) + (uvb * 0.002591)) / 2.0;

  return uvi;
}

int ENVClass::i2cRead(uint8_t address, uint8_t reg)
{
  _wire->beginTransmission(address);
  _wire->write(reg);
  if (_wire->endTransmission(false) != 0) {
    return -1;
  }

  if (_wire->requestFrom(address, 1) != 1) {
    return -1;
  }
  
  return _wire->read();
}

int ENVClass::i2cWrite(uint8_t address, uint8_t reg, uint8_t val)
{
  _wire->beginTransmission(address);
  _wire->write(reg);
  _wire->write(val);
  if (_wire->endTransmission() != 0) {
    return 0;
  }

  return 1;
}

int ENVClass::i2cReadWord(uint8_t address, uint8_t reg)
{
  _wire->beginTransmission(address);
  _wire->write(reg);
  if (_wire->endTransmission(false) != 0) {
    return -1;
  }

  if (_wire->requestFrom(address, 2) != 2) {
    return -1;
  }

  return (_wire->read() | _wire->read() << 8);
}

int ENVClass::i2cWriteWord(uint8_t address, uint8_t reg, uint16_t val)
{
  _wire->beginTransmission(address);
  _wire->write(reg);
  _wire->write(val & 0xff);
  _wire->write(val >> 8);
  if (_wire->endTransmission() != 0) {
    return 0;
  }

  return 1;
}

void ENVClass::readHTS221Calibration()
{
  uint8_t h0rH = i2cRead(HTS221_ADDRESS, 0x30);
  uint8_t h1rH = i2cRead(HTS221_ADDRESS, 0x31);

  uint16_t t0degC = i2cRead(HTS221_ADDRESS, 0x32) | ((i2cRead(HTS221_ADDRESS, 0x35) & 0x03) << 8);
  uint16_t t1degC = i2cRead(HTS221_ADDRESS, 0x33) | ((i2cRead(HTS221_ADDRESS, 0x35) & 0x0c) << 6);

  int16_t h0t0Out = i2cRead16(HTS221_ADDRESS, 0x36);
  int16_t h1t0Out = i2cRead16(HTS221_ADDRESS, 0x3a);

  int16_t t0Out = i2cRead16(HTS221_ADDRESS, 0x3c);
  int16_t t1Out = i2cRead16(HTS221_ADDRESS, 0x3e);

  _hts221HumiditySlope = (h1rH - h0rH) / (2.0 * (h1t0Out - h0t0Out));
  _hts221HumidityZero = (h0rH / 2.0) - _hts221HumiditySlope * h0t0Out;

  _hts221TemperatureSlope = (t1degC - t0degC) / (8.0 * (t1Out - t0Out));
  _hts221TemperatureZero = (t0degC / 8.0) - _hts221TemperatureSlope * t0Out;
}

ENVClass ENV(Wire, LIGHT_SENSOR_PIN);
