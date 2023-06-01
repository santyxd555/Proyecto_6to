#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Alto de la pantalla OLED en píxeles

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Inicializa la comunicación I2C con la pantalla OLED
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  // Muestra el mensaje de bienvenida
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.println("MENU");
  display.display();
  delay(2000);
}

void loop() {
  
  display.clearDisplay();// Limpia la pantalla OLED
  

  display.setTextSize(2);  // Muestra el texto en la pantalla
  display.setTextColor(WHITE);
  display.setCursor(5,20);
  display.println("< MANUAL >");
 

  display.display();  // Actualiza la pantalla OLED
  delay(1000);  // Espera un segundo antes de volver a actualizar la pantalla
}
