void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200, SERIAL_8E1);  // 8 data bits, 1 even parity bit
  // prints title with ending line break
  //Serial.println("ASCII Table - Character Map");

  pinMode(LED_BUILTIN, OUTPUT);
}

int thisByte = 'U';

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.write(thisByte);
  //delay(1000);

  if (Serial.available()) {
    Serial.readStringUntil('\n');
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

    Serial.write(thisByte);
  }
}
