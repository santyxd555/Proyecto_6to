#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int Cuad;
int flg=0;
int Menu;

#define SW 5

#define OLED_ANCHO 128
#define OLED_ALTO 64

Adafruit_SSD1306 display(OLED_ANCHO, OLED_ALTO, &Wire, -1);

int X = analogRead(A0); 
int Y = analogRead(A1);
int mapY = map(Y, 0, 1023, 0, 7); // izquierda-derecha [1-2]
int mapX = map(X, 0, 1023, 7, 0); // arriba - abajo    [3-4] 

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

  case 4:
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("  MODO ");
  display.setCursor(5,20);
  display.println("AUTO. MOVIL");
  display.display();
  break;

  case 5: 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("   90°  ");
  display.setCursor(5,20);
  display.println("  180°  ");
  display.display();
  break;

  case 6:
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println(" Presione ");
  display.setCursor(5,20);
  display.println("Para iniciar");
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

void inicio(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("Iniciando...");
  delay(2000);
  display.clearDisplay();
}

void pano(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("Posicione ");
  display.setCursor(5,20);
  display.println("la camara");
  display.display();
  delay(5000);
  display.clearDisplay();

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println(" Saque");
  display.setCursor(5,20);
  display.println("la foto");
  display.display();
  delay(5000);
  display.clearDisplay();

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.println("Sacando");
  display.setCursor(5,20);
  display.println(" foto...");
  display.display();
  delay(5000);
  display.clearDisplay();
  
Menu=6;}

void loop(){
if(analogRead(SW)==LOW && flg==0)
{inicio();
menu();
Menu=0; flg=1;}

if(Menu==0)
{if(mapY == 7){Cuad=0;}
else if(mapY == 0){Cuad=1;} 
if(mapX == 7) {display.clearDisplay(); Menu=1;}
if(analogRead(SW)==LOW && Cuad==0){
  display.clearDisplay();
  Menu=2;}
if(analogRead(SW)==LOW && Cuad==1){
  display.clearDisplay();
  Menu=3;}
}

if(Menu==1)
{if(mapY == 7){Cuad=0;}
else if(mapY == 0){Cuad=1;} 
if(analogRead(SW)==LOW && Cuad==0){
  display.clearDisplay();
  flg=0;}
if(analogRead(SW)==LOW && Cuad==1){
  display.clearDisplay();
  Menu=0;}
}

if(menu==2)
{if(mapX == 7) {display.clearDisplay(); Menu=0;}}

if(menu==3)
{if(mapY == 7){Cuad=0;}
else if(mapY == 0){Cuad=1;} 
if(mapX == 7) {display.clearDisplay(); Menu=0;}
if(analogRead(SW)==LOW && Cuad==0){
  display.clearDisplay();
  Menu=5;}
if(analogRead(SW)==LOW && Cuad==1){
  display.clearDisplay();
  Menu=4;}
}

if(menu==4)
{if(mapX == 7) {display.clearDisplay(); Menu=3;}}

if(menu==5)
{if(mapY == 7){Cuad=0;}
else if(mapY == 0){Cuad=1;} 
if(mapX == 7) {display.clearDisplay(); Menu=3;}

if(analogRead(SW)==LOW && Cuad==0){
  display.clearDisplay();
  Menu=6;}

if(analogRead(SW)==LOW && Cuad==1){
  display.clearDisplay();
  Menu=6;}
}

if(Menu=6)
{if(mapX == 7) {display.clearDisplay(); Menu=5;}
if(analogRead(SW)==LOW)
{pano();}
}
}