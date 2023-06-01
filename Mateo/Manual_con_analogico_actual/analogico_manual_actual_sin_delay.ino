#include <Servo.h>

Servo servo1;

#define servopin1 11 

int valor1 = 0;

volatile int milis; //mi variable
volatile int seg = 0;       //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

int angulo = 90;
volatile int valorServo = 0;

typedef enum{}

#define pulAnalog 4
int analogY; //para guardar el valor de la variable del analogico
int analogX;

void setup() {
  Serial.begin(9600);    //Iniciando puerto serial

  servo1.attach(servopin1);
  servo1.write(angulo);

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
    analogY = analogRead(A0); //guarda la lo que mide en una variable
    analogX = analogRead(A1);

    valor1 = map(analogY, 0, 1023, 0, 180);/*1° es la variable, 2° y 3° es el maximo y 
    minimo del sensor, y el 4° y 5° son los maximos y minimos que queres ponerle
    */
    switch(valor1)
    {
      case 1:
      
      valorServo = valorServo + 10
      break;

      case 2:
      
      valorServo = valorServo - 10;
      break;

      case 3: 
      
      valorServo = valorServo + 5;
      break;

      case 4: 

      valorServo = valorServo - 5;
      break;

      case 5: 

      valorServo = 180;
      break;

      case 6:

      valorServo = 0;
      break;
    }
   /* if(valor1 >= 120){
    valorServo = valorServo + 10;
    }
    if(valor1 <= 60){
    valorServo = valorServo - 10;
    }
    if(valor1 >= 90){
    valorServo = valorServo + 5;
    }
    if(valor1 <= 90){
    valorServo = valorServo - 5;
    }
    if(valorServo >= 180){
    valorServo = 180;
    }
    if(valorServo <= 0){
    valorServo = 0;
    }
    */

    Serial.print(valor1);
    Serial.print("\t");
    Serial.println(valorServo); //toma el valor del map con los limites 0 y 360
    servo1.write(valorServo); //imprime el valor en el servo

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
