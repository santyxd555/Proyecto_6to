//////////PARTE MENU//////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//////////PARTE MANUAL///////////
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3; //solo se utiliza con el mpu6050

#define servopin1 11
#define servopin2 10
#define servopin3 9 //solo se utiliza con el mpu6050

///////////PARTE MENU//////////
int Cuad;
int Menu;
int Z, X, mapX, mapZ;
int flg1=0, flg2=0, flg3=0;
bool unavez = 0, contador = 0;

#define SW 6 //pulsador del analogico

volatile int milisPano;     //Mi variable para el panoramico 
volatile int milis;         //Mi variable
volatile int milisDelay;    //mi variable de delay
volatile int seg;           //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

#define OLED_ANCHO 128
#define OLED_ALTO 64

Adafruit_SSD1306 display(OLED_ANCHO, OLED_ALTO, &Wire, -1);

////////////PARTE MANUAL////////////
int valor1 = 0;
int valor2 = 0;

volatile int valorServo = 90;  //Valor 0 del servo 1
volatile int valorServo2 = 90; //Valor 0 del servo 2

int analogY; //Valor del analogico en eje Y 
int analogZ; //Valor del analogico en eje Z
int analogX; //Valor del analogico en eje X?

typedef enum{MENU_INICIAL, MODO_MANUAL, MODO_AUTOMATICO, MODO_PANORAMICO, MODO_MOVIL, MODO_PAN_90, MODO_PAN_180, MODO_MAN_FUN, MODO_MOV_FUN, MODO_PAN90_FUN, MODO_PAN180_FUN} estadoMEF;
estadoMEF estadoactual;

typedef enum{CUAD_NADA, CUAD_ABAJO, CUAD_ARRIBA} estadoMEF2;
estadoMEF2 estadocuad;

//el pin del analog del eje Z = A0
//el pin del analog del eje X = A1

void setup() {
/////////PARTE MENU////////////
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(SW, INPUT_PULLUP);

  //Cuenta del timer 2 
  SREG = (SREG & 0b01111111);                //Esta instrucción deshabilita a las interrupciones globales sin modificar el resto de las interrupciones.
  TCNT2 = 0;                                 //Limpiar el registro que guarda la cuenta del Timer-2.
  TIMSK2 =TIMSK2|0b00000001;                 //Habilitación de la bandera 0 del registro que habilita la interrupción por sobre flujo o desbordamiento del TIMER2.
  TCCR2B= 0b0000011; //250khz
  SREG = (SREG & 0b01111111) | 0b10000000;   //Habilitar interrupciones
  // T = 1/250khz = 4uS
  //255*0.125uS = 1mS
  //cuenta cada 1 milisegundos

///////////PARTE MANUAL///////////
  //Para iniciar el puerto serial
  Serial.begin(9600);
  
  servo1.attach(servopin1);
  servo1.write(valorServo);
  servo2.attach(servopin2);
  servo2.write(valorServo2);
  servo3.attach(servopin3);
  servo3.write(valorServo2);

  estadoMEF estadoActual;
  estadoMEF2 estadocuad;
}

void loop(){
////////////PARTE MENU///////////
   while(seg < 2)
    {
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(8,20);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("INICIANDO");
        Serial.println(seg);
        display.display();
    }


menu(); 
cuadrados();
 
Z = analogRead(A0); 
X = analogRead(A1);

// Funcion MAP: el primer valor es la variable, el segundo y el tercero es el maximo y minimo respectivamente del analogico, y el 
// cuarto y el quinto valor son los maximos y minimos que queres ponerle.
mapZ = map(Z, 0, 1023, 180, 0);  
mapX = map(X, 0, 1023, 180, 0);  

if(Menu == MENU_INICIAL)
    {
      if(mapZ >= 120)//para cambiar entre las opciones del menu
        {
        Cuad = CUAD_ABAJO;
        }
      else 
        if(mapZ <= 60)
        {
          Cuad = CUAD_ARRIBA; 
          flg2=1;
        }
  
      if(Cuad == CUAD_ARRIBA && digitalRead(SW) == LOW && flg2==1)
      {
        flg1 = 1;
        flg2 = 0;
        Menu = MODO_MANUAL; 
        Cuad = CUAD_NADA;
      }
    
      if(Cuad == CUAD_ABAJO && digitalRead(SW) == LOW)
      {
        flg1 = 1; 
        flg2= 1; 
        Menu = MODO_AUTOMATICO; 
        Cuad = CUAD_NADA;
      }
    }
    
    ////////////////////////////////////////////
    
    if(milisDelay > 500)
    {
      if(Menu == MODO_MANUAL)
      {
        if(digitalRead(SW) == LOW && flg2==0)
        {
          if(milisDelay > 500)
          {
            Cuad = CUAD_NADA; 
            Menu = MENU_INICIAL; 
            flg1 = 0;
            milisDelay = 0;
          }
        }
      }
      milisDelay = 0;
    }
    
    ////////////////////////////////////////////
    
    if(Menu == MODO_AUTOMATICO && flg2 == 1) // Cambiar las opciones del modo automatico
    { 
      if(mapZ >= 120)//para cambiar entre las opciones del menu
      {
        Cuad = CUAD_ABAJO;
      }
      else 
      if(mapZ <= 60)
      {
        Cuad = CUAD_ARRIBA;
      }
    
      if(digitalRead(SW)==LOW && Cuad == CUAD_ARRIBA)
      {
        Menu = MODO_PANORAMICO;
        Cuad = CUAD_NADA;
      }
    
      if(digitalRead(SW)==LOW && Cuad == CUAD_ABAJO)
      {
        Menu = MODO_MOVIL;
        Cuad = CUAD_NADA;
        flg1=1;
        flg2=0;
        flg3=1;
      }
    
      if(mapX >= 120 && flg1==1)
      {
        if(milisDelay > 300)
        {
          Cuad = CUAD_NADA; 
          Menu = MENU_INICIAL; 
          flg1=0; 
          flg2=0;
          milisDelay = 0;
        }
      }
    }
    
    ///////////////////////////////////////////////////////
    
    if(Menu == MODO_PANORAMICO && flg2 == 1)
    { 
      if(mapZ >= 120){
        Cuad = CUAD_ABAJO;
        } //para cambiar entre las opciones del menu
      else 
      if(mapZ <= 60){
        Cuad = CUAD_ARRIBA;
        }
    
      if(digitalRead(SW)==LOW && Cuad == CUAD_ARRIBA)
      {
        Menu = MODO_PAN_90;
        Cuad = CUAD_NADA;
        flg2=0;
      }
    
      if(digitalRead(SW)==LOW && Cuad == CUAD_ABAJO)
      {
        Menu = MODO_PAN_180;
        Cuad = CUAD_NADA;
        flg2=0;
      }
    
      if(mapX >= 120 && flg1==1)
      {
        if(milisDelay > 300)
        {
          Cuad = CUAD_NADA; 
          Menu = MODO_AUTOMATICO; 
          flg1=1; 
          flg2=1;
          milisDelay = 0;
        }
      }
    }
    
  ///////////////////////////////////////
  
  if(Menu == MODO_MOVIL)
  {
    if(mapX >= 120 && flg1==1)
    {
      if(milisDelay > 300)
      {
        Cuad = CUAD_NADA; 
        Menu = MODO_AUTOMATICO; 
        flg1=0; 
        flg2=1;
        milisDelay = 0;
      }
    }
  }
  
  //////////////////////////////////////////
  
  if(Menu == MODO_PAN_90)
  {
  if(mapX >= 120 && flg2==0)
    {
      Cuad = CUAD_NADA; 
      Menu = MODO_PANORAMICO; 
      flg1=1;
      flg2=1;
      delay(500);
    }
  }
  
  ///////////////////////////////////////
  
  if(Menu == MODO_PAN_180)
  {
  if(mapX >= 120 && flg2==0)
    {
      Cuad = CUAD_NADA; 
      Menu = MODO_PANORAMICO; 
      flg1=1;
      flg2=1;
      delay(500);
    }
  }


/////////////////////////////////////
///////////////////////////////////////////////////////
}

/////////////PARTE  MENU////////////////
void cuadrados(){

   switch(Cuad){
    case CUAD_ABAJO:
      display.drawRect(4,28,122,18,WHITE); //rectangulo de abajo
    break;
    case CUAD_ARRIBA:
      display.drawRect(4,8,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
    3° ancho del cuadrado, 4° alto del cuadrado */
    break;
   }
   display.display();
}

void menu(){
  switch(Menu){
  
  case MENU_INICIAL:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("MANUAL");
  display.setCursor(6,30);
  display.println("AUTOMATICO");
  break;

  case MODO_MANUAL:
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(30,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
    display.println(" MODO");
    display.setCursor(6,30);
    display.println("  MANUAL");
    unavez = 1;
    valorServo = 90;
    valorServo2 = 90;
    Menu = MODO_MAN_FUN;
    
  break;

  case MODO_AUTOMATICO:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("PANORAMICO");
  display.setCursor(35,30);
  display.println("MOVIL");
  break;

  case MODO_PANORAMICO:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("90 grados");
  display.setCursor(5,30);
  display.println("180 grados");
  break;

  case MODO_MOVIL:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(8,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("  MODO");
  display.setCursor(6,30);
  display.println(" CRUCERO");
  unavez = 1;
  milisPano = 0;
  Menu = MODO_MOV_FUN;
  break;

  case MODO_PAN_90:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("MODO PAN");
  display.setCursor(5,30);
  display.println("90 grados");
  unavez = 1;
  Menu = MODO_PAN90_FUN;
  break;
  
  case MODO_PAN_180:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("MODO PAN");
  display.setCursor(0,30);
  display.println("180 grados");
  unavez = 1;
  Menu = MODO_PAN180_FUN;
  break;
  
  case MODO_MAN_FUN:
    while(unavez == 1){

      X = analogRead(A0); 
      Z = analogRead(A1);

      // Funcion MAP: el primer valor es la variable, el segundo y el tercero es el maximo y minimo respectivamente del analogico, y el 
      // cuarto y el quinto valor son los maximos y minimos que queres ponerle.
      mapZ = map(Z, 0, 1023, 180, 0);  
      mapX = map(X, 0, 1023, 180, 0);  
          
        if(milis >= 40)
          {
          ////////////////// SERVO 1 //////////////////
    
          //EJE Z POSITIVO
          if(mapZ >= 95){
            valorServo = valorServo + 2;
          }
          if(mapZ >= 140){
            valorServo = valorServo + 3;
          }

          //EJE Z NEGATIVO
          if(mapZ <= 50){
            valorServo = valorServo - 2;
          }
          if(mapZ <= 85){
            valorServo = valorServo - 3;
          }

          //EXTREMOS, MAYOR A 180 Y MENOR A 0 DEL EJE Z
          if(valorServo >= 180){
            valorServo = 180;
          }
          if(valorServo <= 0){
            valorServo = 0;
          }

    ////////////////// SERVO 2 //////////////////
    
          //EJE X POSITIVO
          if(mapX >= 95){
            valorServo2 = valorServo2 - 2;
          }
          if(mapX >= 140){
            valorServo2 = valorServo2 - 4;
          }

          //EJE X NEGATIVO
          if(mapX <= 50){
            valorServo2 = valorServo2 + 2;
          }
          if(mapX <= 85){
            valorServo2 = valorServo2 + 4;
          }

          //EXTREMOS, MAYOR A 180 Y MENOR A 50 DEL EJE Z
          if(valorServo2 >= 180){
            valorServo2 = 180;
          }
          if(valorServo2 <= 50){
            valorServo2 = 50;
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
          servo2.write(valorServo2); //IMPRIME EL VALOR EN EL SERVO X
    
          milis = 0;
          if(digitalRead(SW)==LOW)
            {
              if(milisDelay > 500)
              {
                unavez = 0;
                Menu = MENU_INICIAL;
                valorServo = 90;
                valorServo2 = 90;
                servo1.write(valorServo);
                servo2.write(valorServo2);
                milisDelay = 0;
              }
            }
          }
        
    }
  break;

  case MODO_MOV_FUN: //TODOS andan pero hay que ver lo del delay
    while(unavez == 1 )
    {
      if(milisPano > 100)
      {
        if(digitalRead(SW)==HIGH){
          if(digitalRead(SW)==LOW){
            if(digitalRead(SW)==HIGH){
              unavez = 0;
              Menu = MODO_AUTOMATICO;
              flg2=1;
            }
          }
        }
      } 
    }
  break;

  case MODO_PAN90_FUN:
      valorServo = 135;
      valorServo2 = 90;
      servo1.write(valorServo);
      servo2.write(valorServo2);

    while(unavez == 1)
    {
      if(milisPano > 100)
      {
        if(valorServo >= 45)
        {
          valorServo = valorServo - 5;
          servo1.write(valorServo); //IMPRIME EL VALOR EN EL SERVO Z
          milisPano = 0;
        }
        if(digitalRead(SW)==HIGH){
          if(digitalRead(SW)==LOW){
            if(digitalRead(SW)==HIGH){
              unavez = 0;
              Menu = MODO_PANORAMICO;
              flg2=1;
            }
          }
        }
      }  
    }
  break;

  case MODO_PAN180_FUN:
      valorServo = 180;
      valorServo2 = 90;
      servo1.write(valorServo);
      servo2.write(valorServo2);

    while(unavez == 1)
    {
      if(milisPano > 100)
        {
          if(valorServo >= 0)
          {
            valorServo = valorServo - 5;
            servo1.write(valorServo); //IMPRIME EL VALOR EN EL SERVO Z
            milisPano = 0;
          }
      }
      if(digitalRead(SW)==HIGH){
          if(digitalRead(SW)==LOW){
            unavez = 0;
            Menu = MODO_PANORAMICO;
            flg2=1;
          }
        }
    }
  break;
  }
}


//USAMOS EL TIMER 2 PARA CONTAR EL TIEMPO
ISR(TIMER2_OVF_vect){
  
  miliSegundos++;
  milis++;
  milisPano++;
  milisDelay++;
  
  if(miliSegundos == 1000)  
    {
      seg++;

      miliSegundos=0;
    }
}
