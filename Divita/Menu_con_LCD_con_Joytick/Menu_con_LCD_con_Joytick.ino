#include <LiquidCrystal_I2C.h>

uint8_t button_estate = HIGH;
int   VRx = 0;
int   VRy = 0;
const int SW  = 2;
int   btn_push, mapX, mapY, btnRead, numero_menu = 1, sub_menu = 0, sub_menu2 = 0;
int line[5]={0,1,2,3,4}, line_bk[5], line_bk2[5], index, index2;
LiquidCrystal_I2C lcd(0x27,16,3); 


//////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(SW, INPUT_PULLUP);
    lcd.init();
    lcd.backlight(); 
    }

uint8_t flancoSubida(){
  uint8_t valor_nuevo = digitalRead(SW);
  uint8_t result = button_estate != valor_nuevo && valor_nuevo == 1;
  button_estate = valor_nuevo;
  return result;
  }

int leeJoystick(){
  VRx = analogRead(A0); 
  VRy = analogRead(A1);
  mapX = map(VRx, 0, 1023, 0, 7); // izquierda-derecha [1-2]
  mapY = map(VRy, 0, 1023, 7, 0); // arriba - abajo    [3-4] 
  btn_push = flancoSubida();      // push-Enter        [ 5 ]
                                  // Sin mover Joystick[ 0 ]
  if(mapX == 0){btnRead = 1;}
  else if(mapX == 7) {btnRead = 2;}
       else if( (mapY == 7) && (sub_menu2 == false)) {btnRead = 3;}
            else if( (mapY == 0) && (sub_menu2 == false)) {btnRead = 4;}
                 else if(btn_push == 1) {btnRead = 5;}
                      else btnRead = 0;
  return btnRead;                      
  }

////////////////////////////////////////////////////////////////

//Desliza menu con Joystick en LCD
void selec_menu(){
  switch(btnRead){
  case 4:
        menu_arriba();
        numero_menu+=1;
        if(numero_menu > 5) numero_menu =1; //numero_menu elige el submenu.
  break;
  case 3:
        menu_abajo();
        numero_menu-=1;
        if(numero_menu < 1) numero_menu =5; //numero_menu elige el submenu.
  break;           
  case 2:// HACIA LA DERECHA
      
        sub_menu=true; sub_menu2=true;
        //lcd.clear();
  break;
  case 1://HACIA LA IZQUIERDA
       
        sub_menu=false; sub_menu2=false;
        //lcd.clear();
  break;
  case 5:
        sub_menu=true; sub_menu2=true;
        //lcd.clear();
  break;
  case 0:
       
  break;  
  }
  }

///////////////////////////////////////////////////////////////
 
void menu_arriba(){
    for(int i=4; i>-1; i--) 
  {
     index = i-1;
     line_bk[i] = line[i];  
     if(index < 0) line[i] = line_bk[i+4];
     else line[i] = line[i-1];
  }
}

////////////////////////////////////////////////////

void menu_abajo(){
    for(int j=0; j < 5; j++)
  {
      index2 = j+1;
      line_bk2[j]=line[j];
      if (index2 > 4) line[j]=line_bk2[j-4] ;
      else line[j]=line[j+1];
  }
  }

/////////////////////////////////////////////////////////////

void printMenu(){
 
  lcd.setCursor(0,0);
  lcd.print(">");
    lcd.setCursor(1,line[0]);
    lcd.print("1) M E N U    1 ");
    lcd.setCursor(1,line[1]);
    lcd.print("2) M E N U    2 ");
    lcd.setCursor(1,line[2]);
    lcd.print("3) M E N U    3 ");
    lcd.setCursor(1,line[3]);
    lcd.print("4) M E N U    4 ");
    lcd.setCursor(1,line[4]);
    lcd.print("5) M E N U    5 ");
  }

///////////////////////////////////////////////
  
void printSubMenu(){
    lcd.setCursor(0,0);
    lcd.print(">");
      switch(numero_menu){                   
      case 1:                              
            lcd.setCursor(1,0);
            lcd.print("Temp.      C    ");
            lcd.setCursor(1,1);
            lcd.print("Humd.      %    ");          
      break;
      case 2:
            lcd.setCursor(1,0);
            lcd.print("Voltaje RMS     ");
            lcd.setCursor(1,1);
            lcd.print("        ...     ");
      break;
      case 3:
            lcd.setCursor(1,0);
            lcd.print(" Conexion eth0  ");
            lcd.setCursor(0,1);
            lcd.print("        ...     ");
      break;
      case 4:
            lcd.setCursor(1,0);
            lcd.print(" Puerta Abierta ");
            lcd.setCursor(0,1);
            lcd.print("        ...     ");
      break;
      case 5:
            lcd.setCursor(1,0);
            lcd.print(" Alertas        ");
            lcd.setCursor(0,1);
            lcd.print("        ...     ");
      break;
      }
   }//del if

/////////////////////////////////////////////////////////

void loop() {
  // put your main code here, to run repeatedly:
 
 leeJoystick();
 selec_menu();
 if(!sub_menu)  { printMenu();}
 if(sub_menu2) { printSubMenu();}
  
}
