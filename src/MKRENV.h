#include <Arduino.h>
#include <Wire.h>

class ENVClass {
public:
  ENVClass(TwoWire& wire, int lightSensorPin);

  int begin();
  void end();

  float readTemperature();
  float readHumidity();
  float readPressure();
  float readLux();
  float readUVA();
  float readUVB();
  float readUVIndex();

private:
  int i2cRead(uint8_t address, uint8_t reg);
  int i2cRead16(uint8_t address, uint8_t reg) { 
    return (i2cRead(address, reg) | (i2cRead(address, reg + 1) << 8));
  }
  int i2cWrite(uint8_t address, uint8_t reg, uint8_t val);

  int i2cReadWord(uint8_t address, uint8_t reg);
  int i2cWriteWord(uint8_t address, uint8_t reg, uint16_t val);

  void readHTS221Calibration();

private:
  TwoWire* _wire;
  int _lightSensorPin;

  float _hts221HumiditySlope;
  float _hts221HumidityZero;
  float _hts221TemperatureSlope;
  float _hts221TemperatureZero;
};

extern ENVClass ENV;
