
void pinSetup() {
  int motor1A=2;
  int motor1B=3;
  int motor2A=4;
  int motor2B=5;
  int motor3A=6;
  int motor3B=7;
  int motor4A=8;
  int motor4B=9;
  int motor1s=A0;
  int motor2s=A1;
  int motor3s=A2;
  int motor4s=A3;
  int speed=80;
  for (int i=2; i<=9; i=i+1) {
    pinMode(i, OUTPUT);
  }
  for (int i=2; i<=9; i=i+2) {
    digitalWrite(i, HIGH);
  }
  for (int i=3; i<=9; i=i+2) {
    digitalWrite(i, LOW);
  }
}

void setup() {
  pinSetup();
}

void loop() {
  
}
