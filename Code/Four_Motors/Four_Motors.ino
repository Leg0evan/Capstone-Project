#define BLYNK_TEMPLATE_ID "TMPL2TG8iTMdO"
#define BLYNK_TEMPLATE_NAME "Capstone"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

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
int ogGyro_z;
WidgetLCD lcd(V1);
void takeOff() {  //One button to take off up to five feet.
  //Gyro();
  speed = 0;
  for (int x = 0; x < 180; x = x + 1) {
    esc1.write(speed);
    esc2.write(speed);
    esc3.write(speed);
    esc4.write(speed);
    Serial.println(speed);
    speed = speed + 1;
    delay(100);
  }
}

void land() {
  speed = 180;
  for (int x = 180; x > 0; x = x - 1) {
    esc1.write(speed);
    esc2.write(speed);
    esc3.write(speed);
    esc4.write(speed);
    Serial.println(speed);
    speed = speed - 1;
    delay(100);
  }
}
BLYNK_WRITE(V0) {
  if (param.asInt() == 1) {
    digitalWrite(D3, HIGH);
    digitalWrite(D0, LOW);
    takeOff();
    land();
  } else {
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
  }
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
}

#include "Wire.h"  // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68;  // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z;  // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z;                             // variables for gyro raw data
int16_t temperature;                                        // variables for temperature data

char tmp_str[7];  // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) {  // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
void Gyro() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);                         // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false);              // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true);  // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read();  // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read();  // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read();  // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read() << 8 | Wire.read();      // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read() << 8 | Wire.read();           // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read() << 8 | Wire.read();           // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read() << 8 | Wire.read();           // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  // print out data
  Serial.print(" | gZ = ");
  Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();
}


void setup() {
  esc1.attach(ESC_PIN1, 1000, 2000);
  esc2.attach(ESC_PIN2, 1000, 2000);
  esc3.attach(ESC_PIN3, 1000, 2000);
  esc4.attach(ESC_PIN4, 1000, 2000);
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();
  esc1.write(0);
  esc2.write(0);
  esc3.write(0);
  esc4.write(0);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                  // PWR_MGMT_1 register
  Wire.write(0);                     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  ogGyro_z = gyro_z;
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D0, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void loop() {
  BlynkEdgent.run();
  Gyro();
  delay(100);
}
