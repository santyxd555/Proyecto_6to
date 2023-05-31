#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Variables para la integración
double gyro_x, gyro_y, gyro_z;
double angle_x, angle_y, angle_z;
unsigned long prev_time;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  Serial.println("Testing MPU6050 connections...");
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // Inicializar variables de integración
  gyro_x = 0;
  gyro_y = 0;
  gyro_z = 0;
  angle_x = 0;
  angle_y = 0;
  angle_z = 0;
  prev_time = millis();
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convertir los valores de velocidad angular de los ejes x, y, z a grados por segundo
  double gx_deg = gx / 131.0;
  double gy_deg = gy / 131.0;
  double gz_deg = gz / 131.0;

  // Obtener el tiempo transcurrido desde la última iteración
  unsigned long curr_time = millis();
  double elapsed_time = (curr_time - prev_time) / 1000.0;

  // Integrar los valores de velocidad angular para obtener los ángulos de rotación
  angle_x += gx_deg * elapsed_time;
  angle_y += gy_deg * elapsed_time;
  angle_z += gz_deg * elapsed_time;

  // Actualizar las variables de velocidad angular
  gyro_x = gx_deg;
  gyro_y = gy_deg;
  gyro_z = gz_deg;
  prev_time = curr_time;

  // Imprimir los ángulos de rotación en grados
  Serial.print("Rotation: ");
  Serial.print(angle_x); 
  Serial.print("_X, ");
  Serial.print(angle_y); 
  Serial.print("_Y, ");
  Serial.print(angle_z); 
  Serial.println("_Z");

  delay(100);  // Pequeña espera para que la salida por el puerto serie no sea muy rápida
}
