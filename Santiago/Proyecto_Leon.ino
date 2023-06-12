#include <LiquidCrystal.h>
#include <AccelStepper.h>
LiquidCrystal lcd(13,12,11,10,9,8); 
typedef enum{MENU_INICIAL,MENU_AUTOMATICO,MANUAL} estadoMEF;
estadoMEF estadoactual;
AccelStepper stepper1(1, 3, 12); // (Type of driver: with 2 pins, STEP, DIR)
const int dirpin = 2;
const int stepin = 3;
const int reset = 4;
AccelStepper stepper2(1, 6, 13); // (Type of driver: with 2 pins, STEP, DIR)
const int dirpin2 =  5;
const int stepin2 = 6;
const int reset2 = 7;
//pulsadores
const int arriba = A2;
const int abajo = A3;
const int derecha = A4;
const int izquierda = A5;
const int oka = 1;
//potenciometros
const int pote_cm = A0;
const int pote_cantidad = A1;

int cu=10;
int flg1=0;
int aux=0;
int CM;
int CANTIDAD;
int cuenta_cm;
int cuenta_cantidad; 

volatile int seg;
volatile int minutos;
volatile int segundos;
volatile int miliSegundos; 
volatile int microSegundos; 

void setup()
{
pinMode(oka,INPUT_PULLUP);
stepper1.setMaxSpeed(1000);
pinMode(derecha,INPUT_PULLUP);
pinMode(izquierda,INPUT_PULLUP);
stepper2.setMaxSpeed(1000);
pinMode(arriba,INPUT_PULLUP);
pinMode(abajo,INPUT_PULLUP);
//potenciometros
pinMode(pote_cm,INPUT); 
pinMode(pote_cantidad,INPUT);
//lcd
lcd.begin(16,2);
lcd.clear();
//maquina de estado finito
estadoMEF estadoActual;
estadoActual=MENU_INICIAL;
//cuenta del timer2 
 SREG = (SREG & 0b01111111);      //Esta instrucción deshabilita a las interrupciones globales sin modificar el resto de las interrupciones.
 TCNT2 = 0;     //Limpiar el registro que guarda la cuenta del Timer-2.
 TIMSK2 =TIMSK2|0b00000001;      //Habilitación de la bandera 0 del registro que habilita la interrupción por sobre flujo o desbordamiento del TIMER2.
 TCCR2B= 0b0000011; //250khz
 SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones
// T = 1/250khz = 4uS
//255*0.125uS = 1mS
//cuenta cada 1 milisegundos
}

void loop()
{
  
  switch (estadoactual){

  case MENU_INICIAL:
  
 lcd.setCursor(0,0);
 lcd.print("AUTOMATICO");  
 lcd.setCursor(0,1);
 lcd.print("MANUAL");  
 if(digitalRead(arriba)==LOW)
 {
 estadoactual=MENU_AUTOMATICO;
 }
 if(digitalRead(abajo)==LOW)
 {
 estadoactual=MANUAL;
 }
 break;
   
case MENU_AUTOMATICO:
 
 lcd.setCursor(0,0);
 lcd.print("CM DEL PAPEL:");
 lcd.print(CM);   

 lcd.setCursor(0,1);
 lcd.print("CANTIDAD:");  
 lcd.print(CANTIDAD);

 cuenta_cm=analogRead(pote_cm); 
 CM=(cuenta_cm*30.0)/1023.0; // 30 es la maxima cantidad de cm 
 /*lcd.clear();*/
 cuenta_cantidad=analogRead(pote_cantidad); 
 CANTIDAD=(cuenta_cantidad*50.0)/1023.0; // 50 es la maxima cantidad de tiras de papel 
 /*lcd.clear();*/
 if(digitalRead(oka)==LOW)
 { 
     
      seg=0;
      while(seg<CM)
   {    
     digitalWrite(dirpin, LOW);
     digitalWrite(reset, HIGH);
     stepper1.setSpeed(400);
     stepper1.runSpeed();    
   }
    digitalWrite(reset, HIGH);
    seg=0;
    while(seg<cu){
    digitalWrite(reset2, HIGH);
    digitalWrite(dirpin2, HIGH);
    stepper2.setSpeed(700);
    stepper2.runSpeed();}
      while(seg<20){
    digitalWrite(reset2, HIGH);
    digitalWrite(dirpin2, LOW);
    stepper2.setSpeed(700);
    stepper2.runSpeed();}
 }
 break; 
 
 case MANUAL:
 lcd.clear();
  //motor que mueve la hoja para arriba
  if(digitalRead(arriba)==LOW)
 { 
 digitalWrite(reset, HIGH);
 digitalWrite(dirpin, LOW);
 stepper1.setSpeed(400);
 stepper1.runSpeed();
 }
else{
   digitalWrite(reset, LOW);
 }
//mueve la hoja para abajo
 if(digitalRead(abajo)==LOW)
 { 
 digitalWrite(reset, HIGH);
 digitalWrite(dirpin, HIGH);
 stepper1.setSpeed(400);
 stepper1.runSpeed();
 }
else{
   digitalWrite(reset, LOW);
 }
//mueve a la derecha la cuchilla
  if(digitalRead(derecha)==LOW)
 { 
 digitalWrite(reset2, HIGH);
 digitalWrite(dirpin2, LOW);
 stepper2.setSpeed(700);
 stepper2.runSpeed();
 }
else{
   digitalWrite(reset2, LOW);
 }
//mueve la cuchilla a la izquierda
if(digitalRead(izquierda)==LOW)
 { 
 digitalWrite(reset2, HIGH);
 digitalWrite(dirpin2, HIGH);
 stepper2.setSpeed(700);
 stepper2.runSpeed();
 }
else{
   digitalWrite(reset2, LOW);
 }
 }
 



    
}  

//cuenta segundos con el timer 2
ISR(TIMER2_OVF_vect)
{
  miliSegundos++;
  if(miliSegundos==1000)  
  {
    seg++;
    
    miliSegundos=0;
  }
}
