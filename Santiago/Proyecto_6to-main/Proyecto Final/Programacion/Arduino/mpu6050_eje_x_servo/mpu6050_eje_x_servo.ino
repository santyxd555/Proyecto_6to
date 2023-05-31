#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define ALTO 64
#define ANCHO 128
#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

MPU6050 mpu;
Servo myservo;
Servo myservo2;
Servo myservo3;

int16_t ax, ay, az;
int16_t gx, gy, gz;
float pitch, roll;  //cambiar float por int para que no vibre tanto el servo
int servoPos;
int servoPos2;
int servoPos3;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  myservo.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  
  mpu.initialize();
  Serial.println("MPU6050 inicializado correctamente");

  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  pitch = atan2(ay, az) * RAD_TO_DEG;
  roll = atan2(ax, az) * RAD_TO_DEG;
  
  servoPos = map(ax, 17000, -17000, 0, 180);
  servoPos2 = map(ay, 17000, -17000, 0, 180);
  servoPos3 = map(az, 17000, -17000, 0, 180);
  
  if(servoPos < 0) {
    servoPos = 0;
  }
  else if(servoPos > 180) {
    servoPos = 180;
  }
  
  myservo.write(servoPos);
  myservo2.write(servoPos2);
  myservo3.write(servoPos3);
  
  Serial.print("Ángulo del eje X: ");
  Serial.println(roll);
/*
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(35,15);
  oled.println("Eje X");
  oled.setCursor(20,35);
  oled.println(roll);
  oled.display();
  */
  
  delay(10); // Pequeña espera para evitar la sobrecarga del puerto serie
}
