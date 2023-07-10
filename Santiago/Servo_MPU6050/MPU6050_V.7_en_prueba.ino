/*MPU6050 sensor with servo control.
   https://srituhobby.com
*/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servoY;
Servo servoX;
Servo servoZ;

Adafruit_MPU6050 srituhobby;

void setup() {
  Serial.begin(9600);
   
  servoY.attach(5);
  servoX.attach(6);
  servoZ.attach(9);
   
  Wire.begin();
  srituhobby.begin();
   
  servoY.write(0);
  servoX.write(0);
  servoZ.write(0);

  srituhobby.setAccelerometerRange(MPU6050_RANGE_8_G);//2_G,4_G,8_G,16_G
  srituhobby.setGyroRange(MPU6050_RANGE_500_DEG);//250,500,1000,2000
  srituhobby.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  srituhobby.getEvent(&a, &g, &temp);

  int valor = a.acceleration.y;
  int valor1 = a.acceleration.x;
  int valor2 = a.acceleration.z;


  int value = map(valor,  -10, 10, 180, 0);
  int value1 = map(valor1,  -10, 10, 180, 0);
  int value2 = map(valor2,  -10, 10, 180, 0);


  servoY.write(value); 
  servoX.write(value1); 
  servoZ.write(value2);  

   
  Serial.print("Y:");
  Serial.print(value);
  Serial.print(" /X:");
  Serial.print(value1);
  Serial.print(" /Z:");
  Serial.println(value2);
  //delay(10);

}
