// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor; 
// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int16_t gx, gy, gz; 
long tiempo_prev, dt; 
float girosc_ang_x, girosc_ang_y; 
float girosc_ang_x_prev, girosc_ang_y_prev; 

void setup() { 
 Serial.begin(9600); //Iniciando puerto serial
 Wire.begin(); //Iniciando I2C 
 sensor.initialize(); //Iniciando el sensor
 if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente"); 
 else Serial.println("Error al iniciar el sensor"); 
 tiempo_prev=millis(); 
} 

void loop() { 
 // Leer las velocidades angulares 
 sensor.getRotation(&gx, &gy, &gz); 
 
 //Calcular los angulos rotacion:
 
 dt = millis()-tiempo_prev; 
 tiempo_prev=millis(); 
 
 girosc_ang_x = (gx/131)*dt/1000.0 + girosc_ang_x_prev; 
 girosc_ang_y = (gy/131)*dt/1000.0 + girosc_ang_y_prev; 
 girosc_ang_x_prev=girosc_ang_x; 
 girosc_ang_y_prev=girosc_ang_y; 
 //Mostrar los angulos separadas por un [tab]
 Serial.print("Rotacion en X: "); 
 Serial.print(girosc_ang_x);
 Serial.print("\t Rotacion en Y: "); 
 Serial.println(girosc_ang_y); 
 delay(100); 
} 
