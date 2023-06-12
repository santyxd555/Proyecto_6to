#include <Wire.h>
#include <Servo.h>

Servo servoX, servoY, servoZ;
int posx, posy, posz;

void setup() {
  
  Wire.begin();
  servoX.attach(9);
  servoY.attach(10);
  servoZ.attach(11);
}

void loop() {
  
  Wire.beginTransmission(0x68);//la función Wire.beginTransmission()para iniciar la comunicación con el MPU6050
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);// lee los datos del acelerómetro utilizando la función Wire.requestFrom()
  
  int16_t AcX = Wire.read()<<8|Wire.read();
  int16_t AcY = Wire.read()<<8|Wire.read();
  int16_t AcZ = Wire.read()<<8|Wire.read();

  posx = map(AcX, -17000, 17000, 0, 180);//la función map() para mapear los valores de los ejes X, Y y Z en un rango de 0 a 180 grados que puede ser interpretado por los servomotores
  posy = map(AcY, -17000, 17000, 0, 180);
  posz = map(AcZ, -17000, 17000, 0, 180);

  servoX.write(posx);//la función servo.write() para controlar los servomotores con los valores mapeados
  servoY.write(posy);
  servoZ.write(posz);

  delay(50);
}
