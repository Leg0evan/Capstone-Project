#define BLYNK_TEMPLATE_ID "TMPL2TG8iTMdO"
#define BLYNK_TEMPLATE_NAME "Capstone"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial

#define APP_DEBUG

#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"
#include <Servo.h>

#define ESC_PIN1 D5
#define ESC_PIN2 D6
#define ESC_PIN3 D7
#define ESC_PIN4 D8

Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;
int speed;
int on;
int LEDcolor;
float og_altitude;
float altitude;

#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "Wire.h"
Adafruit_BMP280 bmp;

float getAltitude() {  //Gets Altitude
  return bmp.readAltitude(1013.25) - og_altitude;
}

void altimeter() {             //Setups Altimeter
  while (!Serial) delay(100);  // wait for native usb
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void takeOff() {  //Takes Drone to 1.5m up
  altitude = getAltitude() - og_altitude;
  while (altitude < 1.5) {
    esc1.write(speed);
    esc2.write(speed);
    esc3.write(speed);
    esc4.write(speed);
    Serial.println(speed);
    speed = speed + 1;
    altitude = getAltitude() - og_altitude;
    delay(1000);
  }
}

void land() {  //Takes drone to 0.3m down then drops
  altitude = getAltitude() - og_altitude;
  while (altitude > 0.3) {
    esc1.write(speed);
    esc2.write(speed);
    esc3.write(speed);
    esc4.write(speed);
    Serial.println(speed);
    speed = speed - 1;
    altitude = getAltitude() - og_altitude;
    delay(1000);
  }
  speed = 0;
}

BLYNK_WRITE(V0) {  //Runs takeOff() function
  if (param.asInt() == 1) {
    digitalWrite(D3, HIGH);
    digitalWrite(D0, LOW);
    digitalWrite(D4, LOW);
    takeOff();
  } else {
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
    digitalWrite(D4, LOW);
  }
}
BLYNK_WRITE(V1){
  if (param.asInt()==1){
    digitalWrite(D4, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D0, LOW);
  } else{
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
    digitalWrite(D4, LOW);
  }
}

BLYNK_CONNECTED() {  //Syncs Virtual Pins
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
}

void setup() {
  esc1.attach(ESC_PIN1, 1000, 2000);
  esc2.attach(ESC_PIN2, 1000, 2000);
  esc3.attach(ESC_PIN3, 1000, 2000);
  esc4.attach(ESC_PIN4, 1000, 2000);
  Serial.begin(115200);
  altimeter();
  delay(100);
  BlynkEdgent.begin();
  esc1.write(0);
  esc2.write(0);
  esc3.write(0);
  esc4.write(0);
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D0, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  og_altitude = getAltitude();
}

void loop() {
  BlynkEdgent.run();
  delay(100);
}
