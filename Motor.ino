#include<Servo.h>

#define ESC_PIN D2

Servo esc;
int speed=1;

void setup() 
{
  esc.attach(ESC_PIN,  1000, 2000);
  esc.write(0);
  Serial.begin(9600);
}

void loop() 
{
  for(int x=0; x<181; x=x+1){
    esc.write(speed);
    speed=speed+1;
    delay(100);
    Serial.println(speed);
  }
  for (int x=180; x>-1; x=x-1){
    esc.write(speed);
    speed=speed-1;
    delay(100);
    Serial.println(speed);
  }
  delay(5000);
}
