// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include <Servo.h>

Servo servo1;

#define servopin1 9 

int milis = 0;

volatile int seg;           //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

int angulo = 90;
int valorServo = 0;

#define pulAnalog 4
int analogY; //para guardar el valor de la variable del analogico
int analogX;

void setup() {
  Serial.begin(9600);    //Iniciando puerto serial

  servo1.attach(servopin1);
  servo1.write(angulo);
}

void loop() {

    analogY = analogRead(A0); //guarda la lo que mide en una variable
    analogX = analogRead(A1);
 
    int valor1 = map(analogY, 0, 1023, 0, 180); /*1° es la variable, 2° y 3° es el maximo y 
    minimo del sensor, y el 4° y 5° son los maximos y minimos que queres ponerle
    */

    if(valor1 >= 120)
    valorServo = valorServo + 10;

    if(valor1 <= 60)
    valorServo = valorServo - 10;

    if(valor1 >= 90)
    valorServo = valorServo + 5;

    if(valor1 <= 90)
    valorServo = valorServo - 5;


    if(valorServo >= 180)
    valorServo = 180;

    if(valorServo <= 0)
    valorServo = 0;

    Serial.print(valor1);
    Serial.print("\t");
    Serial.println(valorServo); //toma el valor del map con los limites 0 y 360
    servo1.write(valorServo); //imprime el valor en el servo

    delay(40);
}



//cuenta segundos con el timer 2
ISR(TIMER2_OVF_vect)
{
  miliSegundos++;
  milis = milis + 100;
  if(miliSegundos == 1000)  
  {
    seg++;

    miliSegundos=0;
    }
}
