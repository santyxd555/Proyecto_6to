//#include <TimerOne.h>
#include <LiquidCrystal.h>

#define RIEGO 4
#define LDR A0
#define LM A1
float TEMP;
float LUZ;
int MP;

LiquidCrystal DISP(13,12,11,10,9,8);

void setup() {
 // Timer1.initialize(200000);
 // Timer1.attachInterrupt(CLEAR);
  DISP.begin(16,2);
  DISP.clear();
  pinMode(RIEGO, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2),MANO,FALLING); 
}

void loop() {
  TEMP = analogRead(LM);
  LUZ = analogRead(LDR);

  if(MP==1){
    if(LUZ*5/1023 < 4 && TEMP*5/1023 < 4)
    {
      digitalWrite(RIEGO, LOW);
      DISP.setCursor(0,0);
      DISP.print("TENSION1:");
      DISP.setCursor(10,0);
      DISP.print(LUZ*5/1023);
      DISP.setCursor(0,1);
      DISP.print("TENSION2:");
      DISP.setCursor(10,1);
      DISP.print(TEMP*5/1023);
      delay(200);
      DISP.clear();
    }
    if(LUZ*5/1023 >= 4 || TEMP*5/1023 >= 4)
    {
      digitalWrite(RIEGO, HIGH);
      DISP.setCursor(2,0);
      DISP.print("RIEGO ACTIVADO");
      delay(200);
      DISP.clear();
    }
  }

  if(MP==0){
    DISP.setCursor(2,0);
    DISP.print("PARADA DE");
    DISP.setCursor(3,1);
    DISP.print("EMERGENCIA");
    delay(200);
    DISP.clear();    
  }
  
  
}

void MANO(){
  MP = !MP;
}
/*
void CLEAR(){
  DISP.clear();
}
*/
