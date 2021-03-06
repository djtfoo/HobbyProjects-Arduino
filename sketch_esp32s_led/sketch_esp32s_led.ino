// LED on GPIO23
int ledPin = 23;

void setup() {
  // Set LED as output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(500);

  digitalWrite(ledPin, LOW);
  delay(500);
}
