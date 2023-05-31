#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Alto de la pantalla OLED en píxeles

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define swpin 7
#define Ypin A3
#define Xpin A4

int anguloX = 0;
int anguloY = 0;

void setup() {
  // Inicializa la comunicación I2C con la pantalla OLED
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode (swpin, INPUT);

}

void loop() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(28,15);
  display.println("HOlA");
  display.setCursor(6,38);
  display.println("AUTOMATICO");
  
// int valorSW = digitalRead(swpin);
// int valorY = analogRead(Ypin);
// int valorX = analogRead(Xpin);

int anguloY = map(analogRead(A3), 0, 1023, 0, 2);

int ejeY(anguloY);

delay(1000);
}
/*
void ejeY(int valorx)
{
  switch(valorx) 
  {
    case 0:
    display.drawRect(0, 35, 128, 19, WHITE);
    delay(1000)
    break;

    case 1:
    display.drawRect(0, 14, 128, 18, WHITE);
    delay(1000)
    break;
    }
}
*/
