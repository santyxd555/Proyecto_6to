#define redPin 4
#define greenPin 5
#define bluePin 6

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,HIGH);
  digitalWrite(redPin,HIGH);
  delay(2000);
}
