# Arduino MKR ENV library

The Arduino MKR ENV library allows you to read the sensors on the MKR ENV Shield. It manages the different interfaces used by the sensors on the shield to give you an uniform and simple set of functions to read them. The library takes care of the calculations needed to produce values in the requested units. The values returned are signed floats.

To use this library:

```
#include <Arduino_MKRENV.h>
```

The Arduino MKR ENV library takes care of the sensor initialization and sets its values as follows:

- Absolute pressure range: 260 to 1260 hPa.
- Humidity range: 0 to 100%
- Humidity accuracy: ± 3.5% rH, 20 to +80% rH.
- Temperature range -40 to 120 °C. 
- Temperature accuracy: ± 0.5 °C from 15 to 40 °C.
- Lux range: 10 to 100,000 lux.
- UVA/UVB resolution: 16-bit; unit μW/cm2.
- UVIndex: 1 to 11+.

