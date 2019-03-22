/*
  MKR ENV Shield - Read Sensors

  This example reads the sensors on-board the MKR ENV shield
  and prints them to the Serial Monitor once a second.

  The circuit:
  - Arduino MKR board
  - Arduino MKR ENV Shield attached

  This example code is in the public domain.
*/

#include <Arduino_MKRENV.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(ENV.readTemperature());
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(ENV.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure    = ");
  Serial.print(ENV.readPressure());
  Serial.println(" kPa");

  Serial.print("Lux .       = ");
  Serial.println(ENV.readLux());

  Serial.print("UVA         = ");
  Serial.println(ENV.readUVA());

  Serial.print("UVB         = ");
  Serial.println(ENV.readUVB());

  Serial.print("UV Index    = ");
  Serial.println(ENV.readUVIndex());

  Serial.println();

  delay(1000);
}
