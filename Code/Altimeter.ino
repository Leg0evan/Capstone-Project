#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
 
#define SEALEVELPRESSURE_HPA (1013.25)
 
Adafruit_BME280 bme;
 
float temperature, humidity, pressure, altitude, og_altitude;             
 
void setup() {
  Serial.begin(115200);
  delay(100);
  bme.begin(0x76);
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  og_altitude=altitude;
  Serial.println(altitude);
}

void loop() {
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.println(altitude-og_altitude);
  delay(1000);
}