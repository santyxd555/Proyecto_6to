#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SW 6

int Cuad;
int Menu;
int Y, X, mapX, mapY;
int flg1=0, flg2=0, flg3=0;

volatile int seg;           //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

#define OLED_ANCHO 128
#define OLED_ALTO 64

Adafruit_SSD1306 display(OLED_ANCHO, OLED_ALTO, &Wire, -1);

typedef enum{ESTADO_INICIAL, MODO_MANUAL, PANORAMICO_MOVIL, OPCIONES_GRADOS, MODO_CRUCERO, MODO_PAN_90, MODO_PAN_180} estadoMENU;
estadoMENU estadoActual;


void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(SW, INPUT_PULLUP);

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

// Programa principal
void loop(){

while(seg < 2)
    {
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(8,20);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("INICIANDO");
        Serial.println(seg);
        display.display();

        IniciarMENU();
    }



cuadrados();
 
X = analogRead(A0); 
Y = analogRead(A1);

// Funcion MAP: el primer valor es la variable, el segundo y el tercero es el maximo y minimo respectivamente del analogico, y el 
// cuarto y el quinto valor son los maximos y minimos que queres ponerle.
mapY = map(Y, 0, 1023, 0, 180);  
mapX = map(X, 0, 1023, 0, 180);  

ActualizarMENU();



}


void IniciarMENU(){
estadoActual = ESTADO_INICIAL;
}

void ActualizarMENU(){
switch (estadoActual) {

case ESTADO_INICIAL:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,10);
  display.println("MANUAL");
  display.setCursor(6,30);
  display.println("AUTOMATICO");

  if(mapY >= 120)//para cambiar entre las opciones del menu
    {
      Cuad=1;
    }
    else 
    if(mapY <= 60)
    {
      Cuad=2; 
      flg2=1;
    }

  if(Cuad == 2 && digitalRead(SW) == LOW && flg2==1)
  {
    estadoActual = MODO_MANUAL; 
    Cuad=0;
    flg1=1;
    flg2=0; 
  }

  if(Cuad == 1 && digitalRead(SW) == LOW)
  {
    estadoActual = PANORAMICO_MOVIL;
    Cuad=0;
    flg1=1; 
    flg2= 1;
  }
break;


case MODO_MANUAL:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,10);
  display.println(" MODO");
  display.setCursor(6,30);
  display.println("  MANUAL");
  display.display();

if(digitalRead(SW) == LOW && flg2==0)
  { 
    delay(150);
    estadoActual = ESTADO_INICIAL;
    Cuad=0;
    flg1=0;
  }

break;

case PANORAMICO_MOVIL:


break;

case OPCIONES_GRADOS:

break;

case MODO_CRUCERO:
break;

case MODO_PAN_90:
break;

case MODO_PAN_180:
break;




default:{
//Si algo modificó la variable estadoActual a un estado no válido llevo la MEF a un lugar seguro, por ejemplo, la reinicio:
IniciarMENU();
}
break;
}
}






void cuadrados(){

   switch(Cuad){
    case 1:

      display.drawRect(4,8,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
    3° ancho del cuadrado, 4° alto del cuadrado */
    break;

    case 2:
      display.drawRect(4,28,122,18,WHITE);//rectangulo de abajo
    break;
   }
   display.display();
}


//cuenta segundos con el timer 2
ISR(TIMER2_OVF_vect)
{
  miliSegundos++;
  if(miliSegundos==1000)  
  {
    seg++;
    miliSegundos=0;
  }
}