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
Servo myservo1;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int pitch, roll;  //cambiar float por int para que no vibre tanto el servo

int servoPos;//servo de abajo
float Y = 0.0;
float alpha = 0.18;
float S = Y;

int servoPos1;//servo del medio
float Y1 = 0.0;
float alpha1 = 0.18;
float S1 = Y1;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  myservo.attach(9);
  myservo1.attach(10);
  
  mpu.initialize();
  Serial.println("MPU6050 inicializado correctamente");

  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  pitch = atan2(-ay, -az) * RAD_TO_DEG;
  roll = atan2(ax,  az) * RAD_TO_DEG;
  
  servoPos = map(-ay, 17000, -17000, 0, 180);
  servoPos1 = map(ax, -17000, 17000, 0, 180);

  Y = servoPos;
  S = (alpha*Y)+((1-alpha)*S);//filtro del servo de abajo

  Y1 = servoPos1;
  S1 = (alpha1*Y1)+((1-alpha1)*S1);//filtro del servo del medio

  Serial.println(S);
  Serial.println(S1);
  myservo.write(S);
  myservo1.write(S1);
  
  Serial.print("Ángulo del eje X: ");
  Serial.println(roll);
  Serial.println(pitch);

  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(35,15);
  oled.println("Eje X");
  oled.setCursor(55,35);
  oled.println(roll);
  oled.display();
  
  delay(10); // Pequeña espera para evitar la sobrecarga del puerto serie
}
