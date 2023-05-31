void setup() {
  pinMode(13, OUTPUT); // Configura el pin 13 como salida
}

void loop() {
  digitalWrite(13, HIGH); // Enciende el LED
  delay(2000); // Espera 1 segundo
  digitalWrite(13, LOW); // Apaga el LED
  delay(500); // Espera 1 segundo
}
