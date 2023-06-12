#include <OneWire.h>
#include <DallasTemperature.h>

const int SENSOR_PIN = 4; // El pin utilizado para el bus OneWire.
OneWire oneWire(SENSOR_PIN); // Crea un objeto OneWire en el pin especificado.
DallasTemperature sensors(&oneWire); // Crea un objeto DallasTemperature para interactuar con el sensor.

void setup() {
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios.
  sensors.begin(); // Inicializa el objeto DallasTemperature.
  sensors.setResolution(12); // Configura la resolución del sensor en 12 bits (±0.0625°C).
}

void loop() {
  sensors.requestTemperatures(); // Envía la señal para medir la temperatura.
  float temp = sensors.getTempCByIndex(0); // Obtiene la temperatura en grados Celsius.
  Serial.print("Temperatura actual: ");
  Serial.print(temp);
  Serial.println(" grados Celsius");
  delay(1000); // Espera un segundo antes de volver a medir la temperatura.
}
