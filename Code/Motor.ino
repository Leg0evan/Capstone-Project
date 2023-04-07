#include<Servo.h>

#define ESC_PIN D2

/*
Need to attach a switch to turn off the motor
*/

Servo esc;
int speed;

void takeOff(){
  speed=0;
  for(int x=0; x<180; x=x+1){
    esc.write(speed);
    Serial.println(speed);
    speed=speed+1;
    delay(100);
  }
  delay(1000);
  speed=180;
  for(int x=180; x>0; x=x-1){
    esc.write(speed);
    Serial.println(speed);
    speed=speed-1;
    delay(100);
  }
  delay(5000);
}

void setup() 
{
  esc.attach(ESC_PIN,  1000, 2000);
  Serial.begin(9600);
  esc.write(0);
}

void loop() 
{
takeOff();
}
