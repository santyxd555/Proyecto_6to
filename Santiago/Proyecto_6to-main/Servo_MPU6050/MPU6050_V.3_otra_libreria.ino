#include <Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

Servo servo1;

#define servopin1 9

int ejeZ;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  servo1.attach(servopin1);
}

void loop() {
  ejeZ = mpu6050.getAngleZ();
  
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());

  servo1.write(ejeZ);
}
