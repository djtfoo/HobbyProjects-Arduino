#include <Servo.h>

int i = 0;

int j = 0;

int k = 0;

Servo servo_3;

void setup()
{
  servo_3.attach(3);

}

void loop()
{
  for (i = 0; i <= 120; i += 1) {
    servo_3.write(i);
    delay(50); // Wait for 50 millisecond(s)
  }
  for (k = 120; k >= 0; k -= 1) {
    servo_3.write(k);
    delay(50); // Wait for 50 millisecond(s)
  }
}
