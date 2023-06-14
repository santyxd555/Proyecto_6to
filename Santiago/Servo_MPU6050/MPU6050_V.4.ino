#include <Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

Servo servo1;
Servo servo2;
Servo servo3;

#define servopin1 9
#define servopin2 10
#define servopin3 11


void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo3.attach(servopin3);
}

void loop() {

  float ejeX = mpu6050.getAngleX();
  float ejeY = mpu6050.getAngleY();
  float ejeZ = mpu6050.getAngleZ();
  
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(ejeX);
  Serial.print("\tangleY : ");
  Serial.print(ejeY);
  Serial.print("\tangleZ : ");
  Serial.println(ejeZ);  

  servo1.write(ejeX);
  servo2.write(ejeY);
  servo3.write(ejeZ);
}
