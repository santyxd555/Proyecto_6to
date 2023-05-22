#define PINPOTE A0
float Sa=0;
float alfa=0.1;
float Sm=Sa;

void setup() {
  Serial.begin(9600);
}
void loop() { 
  Sa=(float)analogRead(PINPOTE); //cast a flotante
  Sm=(alfa*Sa)+(1-alfa)*Sm;
  Serial.print(Sa);
  Serial.print(" , ");
  Serial.println(Sm);
  delay(10);
}
