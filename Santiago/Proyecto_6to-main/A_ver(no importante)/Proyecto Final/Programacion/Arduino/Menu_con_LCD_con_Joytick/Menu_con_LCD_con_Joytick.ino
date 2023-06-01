#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección y tamaño del display

int xPin = A0;    // Pin analógico del joystick en el eje X
int yPin = A1;    // Pin analógico del joystick en el eje Y
int buttonPin = 2;  // Pin digital del botón del joystick

int menuCount = 3;    // Número de elementos del menú
int menuIndex = 0;    // Índice actual del elemento del menú

void setup() {
  lcd.init();                      // Inicializar el display LCD
  lcd.backlight();                 // Encender la luz del display LCD
  pinMode(buttonPin, INPUT_PULLUP);  // Configurar el botón del joystick como entrada y activar la resistencia pull-up interna
}

void loop() {
  int xVal = analogRead(xPin);  // Leer el valor del joystick en el eje X
  int yVal = analogRead(yPin);  // Leer el valor del joystick en el eje Y
  int buttonVal = digitalRead(buttonPin);  // Leer el valor del botón del joystick

  // Si el joystick se mueve en el eje X
  if (xVal < 100) {
    menuIndex--;  // Disminuir el índice del menú
    if (menuIndex < 0) {  // Si el índice es menor que 0
      menuIndex = menuCount - 1;  // Volver al último elemento del menú
    }
  } else if (xVal > 900) {  // Si el joystick se mueve en el eje X en la dirección opuesta
    menuIndex++;  // Aumentar el índice del menú
    if (menuIndex >= menuCount) {  // Si el índice es mayor o igual que el número de elementos del menú
      menuIndex = 0;  // Volver al primer elemento del menú
    }
  }
  

  // Actualizar el display LCD con el elemento actual del menú
  lcd.setCursor(0, 0);
  lcd.print("Menu: ");
  lcd.print(menuIndex);

  // Si se presiona el botón del joystick
  if (buttonVal == LOW) {
    // Ejecutar la función correspondiente al elemento actual del menú
    switch (menuIndex) {
      case 0:
        lcd.clear();
        lcd.print("Funcion 0");
        delay(1000);
        break;
      case 1:
        lcd.clear();
        lcd.print("Funcion 1");
        delay(1000);
        break;
      case 2:
        lcd.clear();
        lcd.print("Funcion 2");
        delay(1000);
        break;
    }
  }

  delay(50);  // Pequeña pausa antes de volver a leer los valores del joystick y el botón
}
