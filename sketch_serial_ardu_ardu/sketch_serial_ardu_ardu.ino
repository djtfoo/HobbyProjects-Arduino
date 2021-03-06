#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  // pin2->Rx, pin3->Tx
int newLineSerial = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);  // 8 data bits, no parity, 1 STOP bit
  // prints title with ending line break
  Serial.println("Hardware UART LEFT Up!");

  // configure the data rate of the SW UART
  mySerial.begin(4800); // 8 data bits, no parity, 1 STOP bit
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) { // incoming data from Serial Monitor
    if (newLineSerial)  // if newline character received
    {
      mySerial.write("PC L>> ");
      newLineSerial = false;
    } else {
      int byteRead = Serial.read(); // read from HW UART (data from PC's serial monitor)
      mySerial.write(byteRead); // write to SW UART, which is connected to the SW UART on the other Arduino board
      if (byteRead == '\n') newLineSerial = true;
    }
  }

  if (mySerial.available()) { // incoming data from other Arduino
    Serial.write(mySerial.read());  // output to Serial Monitor
  }
}
