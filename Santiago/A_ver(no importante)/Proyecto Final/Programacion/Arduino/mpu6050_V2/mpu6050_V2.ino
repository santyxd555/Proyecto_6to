#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 mpu;
Servo myservo;

int16_t ax, ay, az;
int16_t gx, gy, gz;
float pitch, roll;
int servoPos;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  myservo.attach(9);
  
  mpu.initialize();
  Serial.println("MPU6050 inicializado correctamente");
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  pitch = atan2(-ay, -az) * RAD_TO_DEG;
  roll = atan2(ax, -az) * RAD_TO_DEG;
  
  servoPos = map(roll, -90, 90, 0, 180);
  
  if(servoPos < roll) {
    servoPos = roll;
  }
  else if(servoPos > roll) {
    servoPos = roll;
  }
  
  myservo.write(servoPos);
  
  Serial.print("Ángulo de balanceo: ");
  Serial.println(roll);
  
  delay(10); // Pequeña espera para evitar la sobrecarga del puerto serie
}
