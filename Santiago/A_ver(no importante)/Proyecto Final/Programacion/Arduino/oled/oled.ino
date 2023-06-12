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
  
  // Muestra el mensaje de bienvenid
}

void loop() {
  // Limpia la pantalla OLED
  display.clearDisplay();
  
  // Muestra el texto "Hola, Mundo!" en la pantalla
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(28,15);
  display.println("MANUAL");
  display.setCursor(6,38);
  display.println("AUTOMATICO");
  
  // Muestra un pequeño rectángulo en la pantalla
  display.drawRect(0, 35, 128, 19, WHITE);
  
  // Actualiza la pantalla OLED
  display.display();
  
  // Espera un segundo antes de volver a actualizar la pantalla
  delay(1000);
}
