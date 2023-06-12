#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <MPU6050.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MPU6050 mpu;
Servo servo;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  servo.attach(9);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  // Leer datos del MPU6050
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convertir los valores del giroscopio a velocidad en grados/s
  float gyroX = gx / 131.0;
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;

  // Calcular la nueva posición del servo basándose en los valores del giroscopio
  float servoAngle = servo.read() + gyroY;

  // Limitar la posición del servo a 0-360 grados
  if (servoAngle < 0) {
    servoAngle = 0;
  }
  if (servoAngle > 360) {
    servoAngle = 360;
  }

  // Enviar la posición al servo
  servo.write(servoAngle);

  // Limpiar la pantalla OLED y mostrar la información
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Servo 360 con MPU6050");
  display.setCursor(0, 10);
  display.print("Angulo: ");
  display.print(servoAngle);
  display.print(" grados");
  display.setCursor(0, 20);
  display.print("Giroscopio X: ");
  display.print(gyroX);
  display.setCursor(0, 30);
  display.print("Giroscopio Y: ");
  display.print(gyroY);
  display.setCursor(0, 40);
  display.print("Giroscopio Z: ");
  display.print(gyroZ);
  display.display();
}
