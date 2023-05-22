#include <Servo.h>

Servo servo1;
Servo servo2;

#define servopin1 9 
#define servopin2 10

int x = 0;
int y = 0;
int angulo = 0;
int angulo1 = 0;


void setup() {
  Serial.begin(9600); 
  
  servo1.attach(servopin1);
  servo1.write(angulo);
  servo2.attach(servopin2);
  servo2.write(angulo1);
}

void loop() {
  x = analogRead(A0);//analogico X
  y = analogRead(A1);//analogico Y
  angulo = map(x, 0, 1023, 0, 180);
  angulo1 = map(y, 0, 1023, 0, 360);
  servo1.write(angulo);
  servo2.write(angulo1);

  Serial.println(angulo1);
  delay(100);
}
