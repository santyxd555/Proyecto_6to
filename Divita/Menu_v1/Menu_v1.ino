#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int Cuad;
int Menu;
int Y, X, mapX, mapY;

#define SW 5

#define OLED_ANCHO 128
#define OLED_ALTO 64

Adafruit_SSD1306 display(OLED_ANCHO, OLED_ALTO, &Wire, -1);


void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(SW, INPUT_PULLUP);
  
}

void menu()
{
  switch(Menu){
  case 0:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("MANUAL");
  display.setCursor(5,20);
  display.println("AUTOMATICO");
  display.display();
  break;

  case 1:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("¿APAGAR?");
  display.setCursor(5,20);
  display.println("SI    NO");
  display.display();
  break;

  case 2:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println(" MODO");
  display.setCursor(5,20);
  display.println("MANUAL");
  display.display();
  break;

  case 3:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("PANORAMICO");
  display.setCursor(5,20);
  display.println(" MOVIL");
  display.display();
  break;
}
}

void cuadrados(){
   switch(Cuad){
     
     case 0:
    display.clearDisplay();
    display.drawRect(2, 18, 124, 20, WHITE);  
    break;

    case 1:
    display.clearDisplay();
    display.drawRect(2, 0, 124, 20, WHITE); 
    break;
   }
}

void loop(){

X = analogRead(A0); 
Y = analogRead(A1);
mapY = map(Y, 0, 1023, 0, 7); // izquierda-derecha [1-2]
mapX = map(X, 0, 1023, 7, 0); // arriba - abajo    [3-4] 

menu();
Menu=0; 
cuadrados();
if(mapY == 7){Cuad=0;}
else if(mapY == 0){Cuad=1;}
}
