// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

Servo servo1;

#define servopin1 9 

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int16_t ax, ay, az;
int16_t gx, gy, gz;

int angulo = 0;

long tiempo_prev;
float dt;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;

void setup() {
  Serial.begin(9600);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  servo1.attach(servopin1);
  servo1.write(angulo);
}

void loop() {
  // Leer las aceleraciones y velocidades angulares
  sensor.getAcceleration(&ax, &ay, &az);//lee la aceleracion 
  sensor.getRotation(&gx, &gy, &gz); //lee la rotacion(giroscopio)
  
  dt = (millis()-tiempo_prev)/1000.0;
  tiempo_prev=millis();
 
  /*Mostrar los angulos separadas por un [tab]
  Serial.print("Rotacion en X:  ");
  Serial.print(ang_x); Serial.print("\t");
  Serial.print("Rotacion en Y: ");
  Serial.print(ang_y); Serial.print("\t");
  Serial.print("Rotacion en Z: ");
  Serial.println(gz);Serial.print("\t");fegrs
  */

  int valor = map(gz, -32750, 32750, 0, 180); /*1° es la variable, 2° y 3° es el maximo y 
  minimo del sensor, y el 4° y 5° son los maximos y minimos que queres ponerle
  */
  
  Serial.println(valor); //toma el valor del map con los limites 0 y 360
  servo1.write(valor); //imprime el valor en el servo
}
