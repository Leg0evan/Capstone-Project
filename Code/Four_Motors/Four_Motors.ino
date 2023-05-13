#define BLYNK_TEMPLATE_ID "TMPL2TG8iTMdO"
#define BLYNK_TEMPLATE_NAME "Capstone"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#define APP_DEBUG

#define USE_NODE_MCU_BOARD

const char* ssid = "Fisher";
const char* password = "bludomain08";

#include "BlynkEdgent.h"
#include <Servo.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "Wire.h"

#define ESC_PIN1 D5
#define ESC_PIN2 D6
#define ESC_PIN3 D7
#define ESC_PIN4 D8

Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;
int hoverSpeed = 100;
int riseSpeed;
int turnSpeed = 95;
int speed1 = 0;
int speed2 = 0;
int speed3 = 0;
int speed4 = 0;
int on;
int LEDcolor;


Adafruit_BMP280 bmp;


void sendSpeed() {  //Sends the Speed to Blynk
  Blynk.virtualWrite(V7, riseSpeed);
}




void takeOff() {  //Takes Drone to 1.5m up
  while (speed1 != hoverSpeed + 10) {
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);
    speed1 = speed1 + 1;
    speed2 = speed2 + 1;
    speed3 = speed3 + 1;
    speed4 = speed4 + 1;
    delay(100);
    sendSpeed();
    }
  delay(2000);
  }
  speed1 = hoverSpeed;
  speed2 = hoverSpeed;
  speed3 = hoverSpeed;
  speed4 = hoverSpeed;
  esc1.write(speed1);
  esc2.write(speed2);
  esc3.write(speed3);
  esc4.write(speed4);
  sendSpeed();
}

void land() {  //Takes drone to 0.2m down then drops
  speed1 = hoverSpeed - 5;
  speed2 = hoverSpeed - 5;
  speed3 = hoverSpeed - 5;
  speed4 = hoverSpeed - 5;
  esc1.write(speed1);
  esc2.write(speed2);
  esc3.write(speed3);
  esc4.write(speed4);
  sendSpeed();
  delay(5000);
  }
speed1 = 0;
speed2 = 0;
speed3 = 0;
speed4 = 0;
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

BLYNK_WRITE(V1) {  //Runs land() function
  if (param.asInt() == 1) {
    digitalWrite(D4, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D0, LOW);
    land();
  } else {
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
    digitalWrite(D4, LOW);
  }
}

BLYNK_WRITE(V2) {  //Goes Forward
  if (param.asInt() == 1) {
    speed1 = turnSpeed;
    speed2 = turnSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D0, LOW);
  } else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
  }
}

BLYNK_WRITE(V3) {  //Goes Backward
  if (param.asInt() == 1) {
    speed3 = turnSpeed;
    speed4 = turnSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D0, LOW);
  } else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
  }
}

BLYNK_WRITE(V4) {  //Goes Left
  if (param.asInt() == 1) {
    speed1 = turnSpeed;
    speed3 = turnSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D0, LOW);
  } else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
  }
}

BLYNK_WRITE(V5) {  //Goes Right
  if (param.asInt() == 1) {
    speed2 = turnSpeed;
    speed4 = turnSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D0, LOW);
  } else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
    digitalWrite(D4, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D0, HIGH);
  }
}

// BLYNK_WRITE(V6) {
// Pin Not Needed
// }

BLYNK_WRITE(V7) {  //Gets the Motor Speed From Slider Widget
  riseSpeed = param.asInt() + hoverSpeed;
}

BLYNK_WRITE(V8) {  //Turns Left
  if (param.asInt() == 1) {
    speed1 = hoverSpeed + 5;
    speed2 = hoverSpeed - 5;
    speed3 = hoverSpeed + 5;
    speed4 = hoverSpeed - 5;
  } else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
  }
}

BLYNK_WRITE(V9) {  //Turns Right
  if (param.asInt() == 1) {
    speed1 = hoverSpeed - 5;
    speed2 = hoverSpeed + 5;
    speed3 = hoverSpeed - 5;
    speed4 = hoverSpeed + 5;
  } else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
  }
}

BLYNK_CONNECTED() {  //Syncs Virtual Pins
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
  Blynk.syncVirtual(V9);
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
}


void loop() {
  }
  sendSpeed();
  BlynkEdgent.run();
  delay(100);
}
