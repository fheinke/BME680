//==================================================================================================
//  Felix Heinke
//
//  Pinout:
//  =======
//  ESP32 DevkitC | BME680 | Comment
//  ------------- | ------ | -------
//  3V3           | 2-6V   | 3.3 Volt input
//  GND           | GND    |
//  G21; GPIO21   | SDA    | SDA
//  G22; GPIO22   | SCL    | SCL
//==================================================================================================



//==================================================================================================
//  Include Librarys
//==================================================================================================
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"



//==================================================================================================
//  Initial Informations
//==================================================================================================
#define SEALEVELPRESSURE_HPA    (1013.25)
#define BME680_I2CADDRESS       (0x76)

Adafruit_BME680 bme;

float bme_temperature;
float bme_pressure;
float bme_humidity;
float bme_gas_resistance;
float bme_gas_quality;
float bme_altitude;



//==================================================================================================
//  Setup Loop
//==================================================================================================
void setup() {
  //  Initialize Serial Console
  Serial.begin(115200);
  Serial.println();

  //  Check if BME680 Sensor is connected
  Serial.println(F("BME680 test"));
  if (!bme.begin(BME680_I2CADDRESS)) {
    Serial.println(F("Couldn't find any valid BME680 sensor!"));
    while (1);
  }

  //  Initialize BME680
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}



//==================================================================================================
//  Main Loop
//==================================================================================================
void loop() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  bme_temperature = bme.temperature;
  bme_pressure = bme.pressure / 100.0;
  bme_humidity = bme.humidity;
  bme_gas_resistance = bme.gas_resistance / 1000.0;
  bme_gas_quality = (bme_gas_resistance / 200) * 100;
  bme_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  
  Serial.print("Temperature = ");
  Serial.print(bme_temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme_pressure);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme_humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme_gas_resistance);
  Serial.println(" KOhms");

  Serial.print("Gas Quality = ");
  Serial.print(bme_gas_quality);
  Serial.println(" %");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme_altitude);
  Serial.println(" m");

  Serial.println();
  delay(2000);
}
