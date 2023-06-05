// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include <Servo.h>

Servo servo1;
Servo servo2;

#define servopin1 11 
#define servopin2 10 

int valor1 = 0;
int valor2 = 0;

volatile int milis; //mi variable
volatile int seg = 0;       //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

volatile int valorServo = 90;
volatile int valorServo2 = 90;


#define pulAnalog 4
int analogY; //para guardar el valor de la variable del analogico
int analogX;

void setup() {
  Serial.begin(9600);    //Iniciando puerto serial

  servo1.attach(servopin1);
  servo1.write(valorServo);
  servo2.attach(servopin2);
  servo2.write(valorServo2);

  //cuenta del timer2 
 SREG = (SREG & 0b01111111);      //Esta instrucción deshabilita a las interrupciones globales sin modificar el resto de las interrupciones.
 TCNT2 = 0;     //Limpiar el registro que guarda la cuenta del Timer-2.
 TIMSK2 =TIMSK2|0b00000001;      //Habilitación de la bandera 0 del registro que habilita la interrupción por sobre flujo o desbordamiento del TIMER2.
 TCCR2B= 0b0000011; //250khz
 SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones
// T = 1/250khz = 4uS
//255*0.125uS = 1mS
//cuenta cada 1 milisegundos
}



void loop() {

    if(milis >= 40)
    {
    analogX = analogRead(A0); //guarda la lo que mide en una variable
    analogY = analogRead(A1);

    valor1 = map(analogX, 0, 1023, 0, 180);/*1° es la variable, 2° y 3° es el maximo y 
    minimo del sensor, y el 4° y 5° son los maximos y minimos que queres ponerle
    */
    valor2 = map(analogY, 0, 1023, 0, 180);/*1° es la variable, 2° y 3° es el maximo y 
    minimo del sensor, y el 4° y 5° son los maximos y minimos que queres ponerle
    */

    //Servo 1

    if(valor1 >= 140){
    valorServo = valorServo + 5;
    }

    if(valor1 <= 50){
    valorServo = valorServo - 5;
    }

    if(valor1 >= 95){
    valorServo = valorServo + 5;
    }

    if(valor1 <= 85){
    valorServo = valorServo - 5;
    }

    if(valorServo >= 180){
    valorServo = 180;
    }

    if(valorServo <= 0){
    valorServo = 0;
    }

    //Servo 2
    if(valor2 >= 140){
    valorServo2 = valorServo2 - 5;
    }

    if(valor2 <= 50){
    valorServo2 = valorServo2 + 5;
    }

    if(valor2 >= 95){
    valorServo2 = valorServo2 - 5;
    }

    if(valor2 <= 85){
    valorServo2 = valorServo2 + 5;
    }

    if(valorServo2 >= 180){
    valorServo2 = 180;
    }

    if(valorServo2 <= 0){
    valorServo2 = 0;
    }

    /* Serial.print(valor1);
    Serial.print("\t");
    Serial.println(valorServo); //toma el valor del map con los limites 0 y 360
    */
    servo1.write(valorServo); //imprime el valor en el servo

    Serial.print(valor2);
    Serial.print("\t");
    Serial.println(valorServo2);
    servo2.write(valorServo2);

     milis = 0;
    }
}



//cuenta segundos con el timer 2
ISR(TIMER2_OVF_vect)
{
  miliSegundos++;
  milis++;
  if(miliSegundos == 1000)  
  {
    seg++;

    miliSegundos=0;
    }
}
