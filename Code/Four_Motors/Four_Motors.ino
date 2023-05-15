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
#include "Wire.h"

#define ESC_PIN1 D5
#define ESC_PIN2 D3
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
int takesOff = 0;

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
    }
  delay(2000);
  speed1 = hoverSpeed;
  speed2 = hoverSpeed;
  speed3 = hoverSpeed;
  speed4 = hoverSpeed;
  esc1.write(speed1);
  esc2.write(speed2);
  esc3.write(speed3);
  esc4.write(speed4);

  takesOff = 1;
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

  delay(5000);
  speed1 = 0;
  speed2 = 0;
  speed3 = 0;
  speed4 = 0;
  takesOff = 0;
}

BLYNK_WRITE(V0) {  //Runs takeOff() function
  if (param.asInt() == 1) {
    takeOff();
    takesOff = 1;
  } 
  else if (takesOff == 1) {
    esc1.write(hoverSpeed);
    esc2.write(hoverSpeed);
    esc3.write(hoverSpeed);
    esc4.write(hoverSpeed);
  }
  else {
    esc1.write(0);
    esc2.write(0);
    esc3.write(0);
    esc4.write(0);
  }
}

BLYNK_WRITE(V1) {  //Runs land() function
  if (param.asInt() == 1) {
    land();
    takesOff = 0;
  }
}

BLYNK_WRITE(V2) {  //Pitch Forward
  if (param.asInt() == 1) {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed + 5;
    speed4 = hoverSpeed + 5;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);

  } 
  else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;

  }
}

BLYNK_WRITE(V3) {  //Pitch Backward
  if (param.asInt() == 1) {
    speed1 = hoverSpeed + 5;
    speed2 = hoverSpeed + 5;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);

  } 
  else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;

  }
}

BLYNK_WRITE(V4) {  //Pitch Left
  if (param.asInt() == 1) {
    speed1 = hoverSpeed + 5;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed + 5;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);

  } 
  else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;

  }
}

BLYNK_WRITE(V5) {  //Pitch Right
  if (param.asInt() == 1) {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed + 5;
    speed3 = hoverSpeed + 5;
    speed4 = hoverSpeed;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);

  } 
  else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;

  }
}

BLYNK_WRITE(V9) { //Throttle Down
  if (param.asInt() == 1) {
    speed1 - 5;
    speed2 - 5;
    speed3 - 5;
    speed4 - 5;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);

  }
  else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);
  }
}

BLYNK_WRITE(V7) {  //Throttle Up
  if (param.asInt() == 1) {
    speed1 + 5;
    speed2 + 5;
    speed3 + 5;
    speed4 + 5;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);

  }
  else {
    speed1 = hoverSpeed;
    speed2 = hoverSpeed;
    speed3 = hoverSpeed;
    speed4 = hoverSpeed;
    esc1.write(speed1);
    esc2.write(speed2);
    esc3.write(speed3);
    esc4.write(speed4);
  }
}

BLYNK_WRITE(V8) {  //Yaw Left
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
  esc1.write(speed1);
  esc2.write(speed2);
  esc3.write(speed3);
  esc4.write(speed4);
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
  esc1.write(speed1);
  esc2.write(speed2);
  esc3.write(speed3);
  esc4.write(speed4);
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
  delay(100);
  BlynkEdgent.begin();
  esc1.write(0);
  esc2.write(0);
  esc3.write(0);
  esc4.write(0);
}


void loop() {
  BlynkEdgent.run();
}
