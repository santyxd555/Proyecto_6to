#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#define MPU 0x68 //Direccion i2c del mpu6050

Servo ServoX, ServoY;
double AcX, AcY, AcZ;
int Pitch, Roll;

void setup(){
  Serial.begin(9600);
  ServoX.attach(8);
  ServoY.attach(9);
  init_MPU(); //Inicializar el MPU6050
}

void loop(){
  FuncionsMPU(); //se adquieren los ejes acX, acY y acZ.

  Roll = FuntionsPitchRoll(AcX, AcZ, AcY); //calculo del angulo roll
  Pitch = FuntionsPitchRoll(AcY, AcX, AcZ); //calculo del angulo pitch

  int ServoRoll = map(Roll, -90, 90, 0, 179);
  int ServoPitch = map(Pitch, -90, 90, 179, 0);

  ServoX.write(ServoRoll);
  ServoY.write(ServoPitch);

  Serial.print("Pirch: "); Serial.print(Pitch);
  Serial.print("\t");
  Serial.print("Roll: "); Serial.print(Roll);
  Serial.print("\n");
}

void init_MPU(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);     //se setea a cero
  Wire.endTransmission(true);
  delay(1000);
}

//Funcion para el Pitch y Roll
double FuntionsPitchRoll(double A, double B, double C){
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B*B) + (C*C);
  DatoB = sqrt(DatoB);

  Value = atan2(DatoA, DatoB);
  Value = Value * 180/3.14;

  return (int)Value;
}

//adquiere los ejes X, Y y Z del MPU 6050
void FuncionsMPU(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  AcX = Wire.read()<<8|Wire.read();
  AcY = Wire.read()<<8|Wire.read();
  AcZ = Wire.read()<<8|Wire.read();
}
