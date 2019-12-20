# BME680
This sketch contains a simple example how a BME680 sensor can be read out. In addition, it is calculated in percent how good the current air quality is.

The I2C address should be set according to the type of sensor. Since the sensor needs the current seal level pressure for the calculation of the correct height in meters, this should be entered under "SEALEVELPRESSURE_HPA".

---

### Pinout:
ESP32 DevkitC | BME680 | Comment
------------- | ------ | -------
3V3 | 2-6V | 3.3 Volt input
GND | GND |
G21; GPIO21 | SDA
G22; GPIO22 | SCL
