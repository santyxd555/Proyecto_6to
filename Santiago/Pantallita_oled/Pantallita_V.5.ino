#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Alto de la pantalla OLED en píxeles

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

typedef enum{MENU_MANUAL, MENU_AUTOMATICO, MODO_AUTOMATICO_1, MODO_AUTOMATICO_2, PANO_PRIMER, PANO_SEGUNDO} estadoMEF;
estadoMEF estadoactual;


volatile int seg;           //timer 2
volatile int minutos;       //timer 2
volatile int segundos;      //timer 2
volatile int miliSegundos;  //timer 2
volatile int microSegundos; //timer 2

#define pulAnalog 4
int analogY; //para guardar el valor de la variable del analogico
int analogX;
int flg1 = 0; //sirve para poder cambiar entre modos y que no tenga ningun problema
int num = 2;

void setup() {
  // Inicializa la comunicación I2C con la pantalla OLED
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  Serial.begin(9600);

  pinMode(pulAnalog, INPUT_PULLUP);

  estadoMEF estadoActual;


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

    while(seg < 2)
    {
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(8,20);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("INICIANDO");
        Serial.println(seg);
        display.display();
    }



    analogY = analogRead(A0); //guarda la lo que mide en una variable
    analogX = analogRead(A1);

    Serial.print(analogY); //muetra los valores en el serial
    Serial.print("  ");
    Serial.println(analogX);
 

  switch(estadoactual)
  {
    case MENU_MANUAL: //Aparece el menu con la opcion manual (que esta seleccionada) y la opcion automatica
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

    case MENU_AUTOMATICO: //Aparece el menu con la opcion manual y la opcion automatica(que esta seleccionada)
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

    case MODO_AUTOMATICO_1: /*este es el modo automatico con las opciones panoramica 
    (que esta seleccionada) y la opcion movil*/
    {
        display.clearDisplay();// Limpia la pantalla OLED
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(5,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("PANORAMICA");
        display.drawRect(4,8,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
        3° ancho del cuadrado, 4° alto del cuadrado */
        display.setCursor(35,30);
        display.println("MOVIL");
    }
    break;

    case MODO_AUTOMATICO_2: /*este es el modo automatico con las opciones panoramica 
    y la opcion movil (que esta seleccionada)*/
    {
        display.clearDisplay();// Limpia la pantalla OLED
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(5,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("PANORAMICA");
        display.drawRect(4,28,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
        3° ancho del cuadrado, 4° alto del cuadrado */
        display.setCursor(35,30);
        display.println("MOVIL");
    }
    break;

    case PANO_PRIMER:
    {
        display.clearDisplay();// Limpia la pantalla OLED
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(5,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("90°");
        display.drawRect(4,8,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
        3° ancho del cuadrado, 4° alto del cuadrado */
        display.setCursor(35,30);
        display.println("180°");
    }
    break;

    case PANO_SEGUNDO:
    {
        display.clearDisplay();// Limpia la pantalla OLED
        display.setTextSize(2);  // Muestra el texto en la pantalla
        display.setTextColor(WHITE);
        display.setCursor(5,10);//1° IZQUIERDA A DERECHA, 2° ARRIBA PARA ABAJO
        display.println("90°");
        display.drawRect(4,28,122,18,WHITE);/*1° izquierda a derecha, 2°de arriba a abajo
        3° ancho del cuadrado, 4° alto del cuadrado */
        display.setCursor(35,30);
        display.println("180°");
    }
    break;
  }

    if(analogY >= 800 && flg1 == 1) //sirve para poder cambiar entre modos y la flg sirve para que no puedas cambiar de modos de una mejor manera
    {
        estadoactual = estadoactual - 1;
        flg1 = 0;
    }
    if(analogY <= 200 && flg1 == 0)
    {
        estadoactual = estadoactual + 1;
        flg1 = 1;
    }


    if(estadoactual == MENU_AUTOMATICO && digitalRead(pulAnalog) == LOW)
    {
        estadoactual = MODO_AUTOMATICO_1; //esto sirve para que cuando cambias de modo puedas seleccioanr el siguiente sin problemas
        flg1 = 0;
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
