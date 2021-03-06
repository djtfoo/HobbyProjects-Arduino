#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(10, 9); // Create MFRC522 instance
byte id[4]; // array to store card ID

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  Serial.println("Ready! Present NFC card to display UID and Type ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!mfrc522.PICC_IsNewCardPresent()) return;  // Look for new cards
  if (!mfrc522.PICC_ReadCardSerial()) return; // Select one of the cards

  // Read card ID and display in hexadecimal
  Serial.print("Card ID:");
  for (byte i = 0; i < 4; ++i) {
    id[i] = mfrc522.uid.uidByte[i];
    Serial.print(id[i] < 0x10 ? " 0" : " ");
    Serial.print(id[i], HEX);
  }

  // Read card type
  byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print(" Type: ");
  Serial.print(mfrc522.PICC_GetTypeName(piccType));
  Serial.println();

  mfrc522.PICC_HaltA(); // Stop reading
}
