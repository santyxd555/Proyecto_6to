#include <Servo.h>
#define PINPOTEX A0 
#define PINPOTEY A1

// Variables del filtro
int N = 10; 
float Sax = 0; // Valor de la señal analogica a filtrar eje x
float Say = 0; // Valor de la señal analogica a filtrar eje y
float alfa = 0.1; 
float Smx = 0; // Valor de la media movil eje x
float Smy = 0; // Valor de la media movil eje y
int potBufferx[10];
int potBuffery[10];

Servo myservo1;
Servo myservo2;
int joyPinX = A0; // Conectar el eje X del joystick al pin analógico 0
int joyPinY = A1; // Conectar el eje Y del joystick al pin analógico 1
int joyMin = 0; // Valor mínimo del joystick
int joyMax = 1023; // Valor máximo del joystick

void setup() {
  myservo1.attach(9); // Conectar el primer servo al pin 9
  myservo2.attach(10); // Conectar el segundo servo al pin 10
}

void loop() {
  /////////////////////////////////////////////////////     SERVO EJE X      ////////////////////////////////////////////////////////////////
  // Leer el valor del potenciómetro y aplicar el filtro para el eje x
  Sax=(float)analogRead(PINPOTEX); 
  Smx=(alfa*Sax)+(1-alfa)*Smx; 
    for (int i = 0; i < N; i++) {
      potBufferx[i] = Smx;
      Smx += 0.1; 
    }
  // Sumar todas las muestras en el buffer del filtro
  int potSumx = 0;
    for(int a = 0; a < N; a++) {
      potSumx += potBufferx[a];
    }
 // Obtener el valor promedio del buffer del filtro
  int potValx = potSumx / N;

  int servoPos1 = map(potValx, joyMin, joyMax, 180, 0); //MAPEO EJE Y del 0 a 180 grado
  myservo1.write(servoPos1); // Mover el primer servo

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////     SERVO EJE Y      ////////////////////////////////////////////////////////////////

  Say=(float)analogRead(PINPOTEY); 
  Smy=(alfa*Say)+(1-alfa)*Smy; 
    for (int i = 0; i < N; i++) {
      potBuffery[i] = Smy;
      Smy += 0.1; 
    }
  // Sumar todas las muestras en el buffer del filtro
  int potSumy = 0;
    for(int a = 0; a < N; a++) {
      potSumy += potBuffery[a];
    }
 // Obtener el valor promedio del buffer del filtro
  int potValy = potSumy / N;

 int servoPos2 = map(potValy, joyMin, joyMax, 180, 0);  //MAPEO EJE Y del 0 a 180 grados
 myservo2.write(servoPos2);

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
