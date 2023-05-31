#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Alto de la pantalla OLED en píxeles

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

typedef enum{MENU_MANUAL,MENU_AUTOMATICO} estadoMEF;
estadoMEF estadoactual;

volatile int seg;           //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

int analogY; //para guardar el valor de la variable del analogico
int analogX;


void setup() {
  // Inicializa la comunicación I2C con la pantalla OLED
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  Serial.begin(9600);
  
  // Muestra el mensaje de bienvenida
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,20);
  display.println("INICIANDO") ;
  display.display();
  delay(2000);

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
    analogY = analogRead(A0); //guarda la lo que mide en una variable
    analogX = analogRead(A1);

    Serial.print(analogY);
    Serial.print("  ");
    Serial.println(analogX);
 
  switch(estadoactual)
  {
    case MENU_MANUAL:
    {
        display.clearDisplay();// Limpia la pantalla OLED
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(30,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("MANUAL");
        display.drawRect(4,8,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
        3° ancho del cuadrado, 4° alto del cuadrado */
        display.setCursor(6,30);
        display.println("AUTOMATICO");
    }
    break;

    case MENU_AUTOMATICO:
    {
        display.clearDisplay();// Limpia la pantalla OLED
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(30,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("MANUAL");
        display.drawRect(4,28,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
        3° ancho del cuadrado, 4° alto del cuadrado */
        display.setCursor(6,30);
        display.println("AUTOMATICO");
    }
    break;
  }

    if(analogY >= 800)
    {
        estadoactual = MENU_MANUAL;
    }
    if(analogY <= 200)
    {
        estadoactual = MENU_AUTOMATICO;
    }


  display.display();  // Actualiza la pantalla OLED
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
