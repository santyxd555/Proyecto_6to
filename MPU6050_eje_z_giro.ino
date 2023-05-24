#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "Servo.h"

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

//declara el servo
Servo servo1;

//declara el pin del servo
#define servopin1 9 

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int gx, gy, gz;

long tiempo_prev, dt;
float girosc_ang_x, girosc_ang_y, girosc_ang_z;
float girosc_ang_x_prev, girosc_ang_y_prev, girosc_ang_z_prev;

void setup() {
  Serial.begin(9600);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  servo1.attach(servopin1);
  servo1.write(0);

}



void loop() {
  // Leer las velocidades angulares 
  sensor.getRotation(&gx, &gy, &gz);
  
  //Calcular los angulos rotacion:
  
  dt = millis()-tiempo_prev;
  tiempo_prev=millis();
  
  girosc_ang_x = (gx/131)*dt/1000.0 + girosc_ang_x_prev;
  girosc_ang_y = (gy/131)*dt/1000.0 + girosc_ang_y_prev;
  girosc_ang_z = (gz/131)*dt/1000.0 + girosc_ang_z_prev;

  girosc_ang_x_prev = girosc_ang_x;
  girosc_ang_y_prev = girosc_ang_y;
  girosc_ang_z_prev = girosc_ang_z;

  //Mostrar los angulos separadas por un [tab]
  Serial.print("  Rotacion en X:  ");
  Serial.print(girosc_ang_x); 
  Serial.print("  Rotacion en Y: ");
  Serial.print(girosc_ang_y);
  Serial.print("  Rotacion en z: ");
  Serial.println(girosc_ang_z);

  //mueve el servo con los valores del giroscopio eje z
  servo1.write(girosc_ang_z);

  delay(100);
}
