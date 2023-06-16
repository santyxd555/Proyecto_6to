#include <Servo.h>

Servo servo1;
Servo servo2;

#define servopin1 11 
#define servopin2 10 

int valor1 = 0;
int valor2 = 0;

volatile int milis;         //Mi variable
volatile int seg = 0;       //Timer 2
volatile int minutos;       //Timer 2
volatile int segundos;      //Timer 2
volatile int miliSegundos;  //Timer 2
volatile int microSegundos; //Timer 2

volatile int valorServo = 90;  //Valor 0 del servo 1
volatile int valorServo2 = 90; //Valor 0 del servo 2


#define pulAnalog 4
int analogY; //Valor del analogico en eje Y 
int analogZ; //Valor del analogico en eje Z

void setup() {

  //Para iniciar el puerto serial
  Serial.begin(9600);
  
  servo1.attach(servopin1);
  servo1.write(valorServo);
  servo2.attach(servopin2);
  servo2.write(valorServo2);

  //Cuenta del timer 2 
  SREG = (SREG & 0b01111111);                //Esta instrucción deshabilita a las interrupciones globales sin modificar el resto de las interrupciones.
  TCNT2 = 0;                                 //Limpiar el registro que guarda la cuenta del Timer-2.
  TIMSK2 =TIMSK2|0b00000001;                 //Habilitación de la bandera 0 del registro que habilita la interrupción por sobre flujo o desbordamiento del TIMER2.
  TCCR2B= 0b0000011; //250khz
  SREG = (SREG & 0b01111111) | 0b10000000;   //Habilitar interrupciones
  // T = 1/250khz = 4uS
  //255*0.125uS = 1mS
  //cuenta cada 1 milisegundos
}



void loop() {

    if(milis >= 40)
    {
        //Lee y guarda en una variable el valor de los analogicos.
        analogZ = analogRead(A0); 
        analogY = analogRead(A1);

        // Funcion MAP: el primer valor es la variable, el segundo y el tercero es el maximo y minimo respectivamente del analogico, y el 
        // cuarto y el quinto valor son los maximos y minimos que queres ponerle.
        valor1 = map(analogZ, 0, 1023, 0, 180);
        valor2 = map(analogY, 0, 1023, 0, 180);

    ////////////////// SERVO 1 //////////////////
    
        //EJE Z POSITIVO
        if(valor1 >= 95){
          valorServo = valorServo + 2;
        }
        if(valor1 >= 140){
          valorServo = valorServo + 3;
        }

        //EJE Z NEGATIVO
        if(valor1 <= 50){
          valorServo = valorServo - 2;
        }
        if(valor1 <= 85){
          valorServo = valorServo - 3;
        }

        //EXTREMOS, MAYOR A 180 Y MENOR A 0 DEL EJE Z
        if(valorServo >= 180){
          valorServo = 180;
        }
        if(valorServo <= 50){
          valorServo = 50;
        }

    ////////////////// SERVO 2 //////////////////
    
        //EJE Y POSITIVO
        if(valor2 >= 95){
          valorServo2 = valorServo2 - 2;
        }
        if(valor2 >= 140){
          valorServo2 = valorServo2 - 4;
        }

        //EJE Y NEGATIVO
        if(valor2 <= 50){
          valorServo2 = valorServo2 + 2;
        }
        if(valor2 <= 85){
          valorServo2 = valorServo2 + 4;
        }

        //EXTREMOS, MAYOR A 180 Y MENOR A 50 DEL EJE Y
        if(valorServo2 >= 180){
          valorServo2 = 180;
        }
        if(valorServo2 <= 0){
          valorServo2 = 0;
        }

     /* VER DE MANERA SERIAL, SERVO 1
        Serial.print(valor1);
        Serial.print("\t");
        Serial.println(valorServo); //toma el valor del map con los limites 0 y 360
     */
        servo1.write(valorServo); //IMPRIME EL VALOR EN EL SERVO Z

     /* VER DE MANERA SERIAL, SERVO 2
        Serial.print(valor2);
        Serial.print("\t");
        Serial.println(valorServo2);
     */
        servo2.write(valorServo2); //IMPRIME EL VALOR EN EL SERVO Y
    
        milis = 0;
    }
}


//Usamos el timer 2 para contar segundos 
ISR(TIMER2_OVF_vect){
  
  miliSegundos++;
  milis++;
  
  if(miliSegundos == 1000)  
    {
      seg++;

      miliSegundos=0;
    }
}
