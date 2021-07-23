# Arduino MKR ENV library

## Methods

### `begin()`

Initialize the sensors on the shield.

#### Syntax 

```
ENV.begin()
```

#### Parameters

None.

#### Returns

1 on success, 0 on failure.

#### Example

```
if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
}
```

#### See also

* [end()](#end)
* [readTemperature()](#readtemperature)
* [readHumidity()](#readhumidity)
* [readPressure()](#readpressure)
* [readIlluminance()](#readilluminance)
* [readUVA()](#readuva)
* [readUVB()](#readuvb)
* [readUVIndex()](#readuvindex)

### `end()`

De-initialize the sensors on the shield.

#### Syntax 

```
ENV.end()
```

#### Parameters

None.

#### Returns

None. 

#### Example

```
ENV.end();
```

#### See also

* [begin()](#begin)
* [readTemperature()](#readtemperature)
* [readHumidity()](#readhumidity)
* [readPressure()](#readpressure)
* [readIlluminance()](#readilluminance)
* [readUVA()](#readuva)
* [readUVB()](#readuvb)
* [readUVIndex()](#readuvindex)

### `readTemperature()`

Read the temperature sensor's value. If no unit is specified as parameter, the value will be expressed in Celsius.

#### Syntax 

```
ENV.readTemperature(unit)
```

#### Parameters

* _unit_: FAHRENHEIT to get the temperature in Fahrenheit and CELSIUS to get the temperature in Celsius (default). 

#### Returns

The sensor’s temperature value as float in the specified unit.

#### Example

```
Serial.print("Temperature = ");
Serial.print(ENV.readTemperature());
Serial.println(" °C");
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readHumidity()](#readhumidity)
* [readPressure()](#readpressure)
* [readIlluminance()](#readilluminance)
* [readUVA()](#readuva)
* [readUVB()](#readuvb)
* [readUVIndex()](#readuvindex)

### `readHumidity()`

Read the humidity sensor's value.

#### Syntax 

```
ENV.readHumidity()
```

#### Parameters

None. 

#### Returns

The temperature sensor’s humidity value as a percentage.

#### Example

```
Serial.print("Humidity    = ");
Serial.print(ENV.readHumidity());
Serial.println(" %");
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readTemperature()](#readtemperature)
* [readPressure()](#readpressure)
* [readIlluminance()](#readilluminance)
* [readUVA()](#readuva)
* [readUVB()](#readuvb)
* [readUVIndex()](#readuvindex)

### `readPressure()`

Read the pressure sensor's value. If no unit is specified, the value will be expressed in kilopascal.

#### Syntax 

```
ENV.readPressure(unit)
```

#### Parameters

* _unit_: PSI to get the pressure in pound per square, MILLIBAR to get the pressure in millibar and KILOPASCAL to get the pressure in kilopascal (default).

#### Returns

The sensor’s pressure value as float in the specified unit.

#### Example

```
Serial.print("Pressure    = ");
Serial.print(ENV.readPressure());
Serial.println(" kPa");
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readTemperature()](#readtemperature)
* [readHumidity()](#readhumidity)
* [readIlluminance()](#readilluminance)
* [readUVA()](#readuva)
* [readUVB()](#readuvb)
* [readUVIndex()](#readuvindex)

### `readIlluminance()`

Read the light sensor’s value.

#### Syntax 

```
ENV.readIlluminance(unit)
```

#### Parameters

* _unit_: FOOTCANDLE to get the light value in footcandle, METERCANDLE to get the light in metercandle and LUX to get the light value in lux (default).

#### Returns

The light sensor's value as float in the specified unit.

#### Example

```
Serial.print("Lux = ");
Serial.println(ENV.readIlluminance());
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readTemperature()](#readtemperature)
* [readHumidity()](#readhumidity)
* [readPressure()](#readpressure)
* [readUVA()](#readuva)
* [readUVB()](#readuvb)
* [readUVIndex()](#readuvindex)

### `readUVA()`

Read the UV sensor’s UV A value.

#### Syntax 

```
ENV.readUVA()   
```

#### Parameters

None. 

#### Returns

The UV sensor's UV A value.

#### Example

```
Serial.print("UVA = ");
Serial.println(ENV.readUVA());
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readTemperature()](#readtemperature)
* [readHumidity()](#readhumidity)
* [readPressure()](#readpressure)
* [readIlluminance()](#readilluminance)
* [readUVB()](#readuvb)
* [readUVIndex()](#readuvindex)

### `readUVB()`

Read the UV sensor’s UV B value.

#### Syntax 

```
ENV.readUVB()   
```

#### Parameters

None. 

#### Returns

The UV sensor's UV B value.

#### Example

```
Serial.print("UVB = ");
Serial.println(ENV.readUVB());
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readTemperature()](#readtemperature)
* [readHumidity()](#readhumidity)
* [readPressure()](#readpressure)
* [readIlluminance()](#readilluminance)
* [readUVA()](#readuva)
* [readUVIndex()](#readuvindex)

### `readUVIndex()`

Read the UV sensor’s UV index value.

#### Syntax 

```
ENV.readUVIndex()
```

#### Parameters

None. 

#### Returns

The UV sensor’s UV index value.

#### Example

```
Serial.print("UV Index = ");
Serial.println(ENV.readUVIndex());
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readTemperature()](#readtemperature)
* [readHumidity()](#readhumidity)
* [readPressure()](#readpressure)
* [readIlluminance()](#readilluminance)
* [readUVA()](#readuva)
* [readUVB()](#readuvb)