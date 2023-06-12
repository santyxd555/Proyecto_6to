#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int Cuad;
int Menu;
int Y, X, mapX, mapY;
int flg1=0, flg2=0;

#define SW 6

volatile int seg;           //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

#define OLED_ANCHO 128
#define OLED_ALTO 64

Adafruit_SSD1306 display(OLED_ANCHO, OLED_ALTO, &Wire, -1);


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

void loop(){

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
 
X = analogRead(A0); 
Y = analogRead(A1);

mapY = map(Y, 0, 1023, 7, 0); // izquierda-derecha [1-2]
mapX = map(X, 0, 1023, 0, 7); // arriba - abajo    [3-4] 


if(Menu == 0 && flg1 == 0 && flg2 == 0)
  {
    if(mapY == 7)//para cambiar entre las opciones del menu
    {
      Cuad=2;
    } 
    else 
    if(mapY == 0)
    {
      Cuad=1;
    }

  if(Cuad == 1 && digitalRead(SW) == LOW)
  {
    flg1=1; 
    Menu=1; 
    Cuad=0;
  }

  if(Cuad == 2 && digitalRead(SW) == LOW)
  {
    flg1=1; 
    flg2= 1; 
    Menu=2; 
    Cuad=0;
  }
}

if(Menu==1 && mapX == 7 && flg1==1)
  {
    Cuad=0; 
    Menu=0; 
    flg1=0;
  }


  if(Menu == 2 && flg2 == 1)
  { 
  if(mapY == 7)//para cambiar entre las opciones del menu
    {
      Cuad=2;
    } 
    else 
    if(mapY == 0)
    {
      Cuad=1;
    }
  }

  if(Menu==2 && mapX == 7 && flg1==1)
  {
    Cuad=0; 
    Menu=0; 
    flg1=0; 
    flg2=0;
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

void menu(){
  switch(Menu){
  case 0:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("MANUAL");
  display.setCursor(6,30);
  display.println("AUTOMATICO");
  break;

  case 1:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println(" MODO");
  display.setCursor(6,30);
  display.println("  MANUAL");
  display.display();
  break;

  case 2:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
  display.println("PANORAMICO");
  display.setCursor(35,30);
  display.println("MOVIL");
  display.display();
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
