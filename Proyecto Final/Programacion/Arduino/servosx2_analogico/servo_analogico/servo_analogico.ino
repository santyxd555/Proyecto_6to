#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int incomingByte = 0;   // for incoming serial data

void setup() {
  Serial.begin(9600);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
}



void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("received: ");
                Serial.print (incomingByte);
                if(incomingByte == 108){
                 Serial.println(" sent 0 Rotaing CW "); 
                 myservo.write(0); 
                }else if(incomingByte == 114){
                  Serial.println(" sent 180 Rotaing CCW "); 
                  myservo.write(180); 
                }else if(incomingByte == 60){
                  Serial.println(" sent Stopped "); 
                  myservo.write(60); 
                }else{
                  Serial.println(" moving Random"); 
                  myservo.write(incomingByte); 
                }
                  
                 
        }

  
} 
