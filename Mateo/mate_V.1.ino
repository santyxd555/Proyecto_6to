#include <Servo.h>
#define PINPOTEX A0 
#define PINPOTEY A1

Servo myservo1;
Servo myservo2;


long velocidad;
long intervalo;
long last_step = 0;
int gradoActual = 90;
bool direcion;
#define maxgrado 180
#define mingrado 0

void setup() {
  myservo1.attach(9); // Conectar el primer servo al pin 9
  myservo2.attach(10); // Conectar el segundo servo al pin 10
  potValx = analogRead(PINPOTEX);
  potValx = map(potValx, joyMin, joyMax, 180, 0);
  myservo1.write(potValx);
}

void loop()
{
  velocidad = map(analogRead(PINPOTEX), 0, 1023, -100, 100);
  if (velocidad){
    direccion = 1;
  }
  else{
    direccion = 0;
    velocidad = velocidad * -1
  }
  intervalo = map(velocidad, -100, 100, 20, 100);
  if (velocidad > 0 && gradoActual < maxgrado && gradoActual > mingrado)
  {
    if (millis() + last_step >= intervalo)
    {
      switch(direccion){
        case 0:
              gradoActual--
              myservo1.write(gradoActual);
              break;
        case 1:
              gradoActual++
              myservo1.write(gradoActual);
              break;
                       }
    }
  }
}
