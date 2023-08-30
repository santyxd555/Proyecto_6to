#include <Wire.h>       
#include <I2Cdev.h>  
#include <MPU6050.h>  
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
#define servopin1 9
#define servopin2 10
#define servopin3 11

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  //pinMode(LED_BUILTIN, OUTPUT);

  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo3.attach(servopin3);
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 180); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 180); 
  data.Z = map(az, -17000, 17000, 0, 180);  // Y axis data
  delay(50);

  Serial.print("  X = ");
  Serial.print(data.X);
  Serial.print("  Y = ");
  Serial.print(data.Y);
  Serial.print("  Z  = ");
  Serial.println(data.Z);

  servo1.write(data.X);
  servo2.write(data.Y);
  servo3.write(data.Z);
}
