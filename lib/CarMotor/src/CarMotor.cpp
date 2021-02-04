#include <CarMotor.h>

int CarMotor::isRun()
{
  return digitalRead(directionPin1) + digitalRead(directionPin2) != 0;
}

void CarMotor::Drive(int speed)
{
  switch (speed)
  {
  case 0:
    digitalWrite(directionPin1, LOW);
    digitalWrite(directionPin2, LOW);
    break;
  case 1:
    digitalWrite(directionPin1, LOW);
    digitalWrite(directionPin2, HIGH);
    break;
  case -1:
    digitalWrite(directionPin1, HIGH);
    digitalWrite(directionPin2, LOW);
    break;
  }
}
