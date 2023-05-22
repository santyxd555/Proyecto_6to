import machine
import utime

sensor_temp = machine.ADC(4) # Crea un objeto ADC para interactuar con el sensor de temperatura.
conversion_factor = 3.3 / (65535) # Factor de conversión para convertir los valores de la lectura en voltios.

while True:
    lectura = sensor_temp.read_u16() * conversion_factor # Lee el valor de la temperatura en voltios.
    temperatura = 27 - (lectura - 0.706)/0.001721 # Calcula la temperatura en grados Celsius.
    print("Temperatura actual: ", temperatura, " grados Celsius")
    utime.sleep(1) # Espera un segundo antes de volver a medir la temperatura.