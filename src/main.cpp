#include <Arduino.h>

class Motor
{

  int directionPin1;
  int directionPin2;

public:
  //Method to define the motor pins
  Motor(int dPin1, int dPin2)
  {
    directionPin1 = dPin1;
    directionPin2 = dPin2;
  };

  //Method to drive the motor 0~255 driving forward. -1~-255 driving backward
  void Drive(int speed)
  {
    if (speed >= 0)
    {
      digitalWrite(directionPin1, LOW);
      digitalWrite(directionPin2, HIGH);
    }
    else
    {
      digitalWrite(directionPin1, HIGH);
      digitalWrite(directionPin2, LOW);
    }
  }
};

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

Motor leftMotor = Motor(motor1pin1, motor1pin2);
Motor rightMotor = Motor(motor2pin1, motor2pin2);

void setup()
{
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // Set initial direction
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void loop()
{
  leftMotor.Drive(200);
  rightMotor.Drive(200);

  delay(500);

  leftMotor.Drive(0);
  rightMotor.Drive(0);

  delay(250);

  leftMotor.Drive(150);
  rightMotor.Drive(-150);

  delay(500);

  leftMotor.Drive(0);
  rightMotor.Drive(0);

  delay(250);
}