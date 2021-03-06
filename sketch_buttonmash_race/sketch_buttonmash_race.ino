/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int p1ButtonPin = 8;
const int p2ButtonPin = 9;
const int resetButtonPin = 6;

int reset_lastState = 0;
int p1_lastState = 0;
int p2_lastState = 0;

const int pressesPerStep = 4;
int p1_numPress = 0;
int p2_numPress = 0;
int p1_char = 1;
int p2_char = 2;

bool win = false;

byte customFlag[8] = {
  0b11000,
  0b11000,
  0b00110,
  0b00110,
  0b11000,
  0b11000,
  0b00110,
  0b00110
};

void setup() {
  lcd.createChar(0, customFlag);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //  lcd.print("hello, world!");

  // set up buttong
  pinMode(p1ButtonPin, INPUT);
  pinMode(p2ButtonPin, INPUT);
  pinMode(resetButtonPin, INPUT);

  initGame();
}

void initGame() {
  lcd.setCursor(15, 0);
  lcd.write((uint8_t)0);
  lcd.setCursor(15, 1);
  lcd.write((uint8_t)0);

  p1_numPress = 0;
  p2_numPress = 0;

  win = false;
}

void playWinTone() {
      tone(7, 330, 300);
      delay(400);
      tone(7, 294, 200);
      delay(250);
      tone(7, 330, 600);
      delay(700);
      tone(7, 262, 450);
      delay(500);
      tone(7, 294, 500);
      delay(550);
      tone(7, 330, 300);
      delay(350);
      tone(7, 294, 200);
      delay(250);
      tone(7, 330, 600);
      delay(700);
}

void printPlayerPos(int p1_step, int p2_step) {
      // print p1 position
      //lcd.setCursor(p1_step, 0);
      //lcd.print(p1_char);
      // print p2 position
      //lcd.setCursor(p2_step, 1);
      //lcd.print(p2_char);

      // print p1
      lcd.setCursor(0, 0);
      for (int i = 0; i < p1_step; i++) {
        lcd.print(".");
      }
      lcd.print(p1_char);
      // print p2
      lcd.setCursor(0, 1);
      for (int i = 0; i < p2_step; i++) {
        lcd.print(".");
      }
      lcd.print(p2_char);
}

void loop() {

  // print the number of seconds since reset:
  //    lcd.print(millis() / 1000);

  // read button
  int p1_buttonState = digitalRead(p1ButtonPin);
  int p2_buttonState = digitalRead(p2ButtonPin);
  int reset_buttonState = digitalRead(resetButtonPin);

  if (win == false) {
    if (p1_buttonState == LOW) {
      if (p1_lastState != p1_buttonState) {
        p1_numPress++;
      }
    }
    if (p2_buttonState == LOW) {
      if (p2_lastState != p2_buttonState) {
        p2_numPress++;
      }
    }

    int p1_step = p1_numPress / pressesPerStep;
    int p2_step = p2_numPress / pressesPerStep;

    if (p1_step >= 15 && p2_step >= 15) {
      win = true;
      lcd.clear();
      lcd.print("Draw!");
      playWinTone();
    }
    else if (p1_step >= 15) {
      win = true;
      lcd.clear();
      lcd.print("P1 Wins");
      playWinTone();
    }
    else if (p2_step >= 15) {
      win = true;
      lcd.clear();
      lcd.print("P2 Wins");
      playWinTone();
    }
    else {
      printPlayerPos(p1_step, p2_step);
    }
  } // win == false

  if (reset_buttonState == LOW) {
    if (reset_lastState != reset_buttonState) {
      lcd.clear();
      initGame();
    }
  }

  reset_lastState = reset_buttonState;
  p1_lastState = p1_buttonState;
  p2_lastState = p2_buttonState;
}
