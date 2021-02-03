#include <Arduino.h>
#include "IRremote.h"

int receiver = 9;

IRrecv irrecv(receiver);
decode_results results;

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
};

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

Motor leftMotor = Motor(motor1pin2, motor1pin1);
Motor rightMotor = Motor(motor2pin2, motor2pin1);


void setup()
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();

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
void translateIR()

{
  Serial.println(results.value);

  switch (results.value)

  {

    case 10042053:
      Serial.println("FORWARD");

      leftMotor.Drive(1);
      rightMotor.Drive(1);
      break;

    case 10091013:
      Serial.println("RIGHT");

      leftMotor.Drive(1);
      rightMotor.Drive(0);
      break;

    case 10058373:
      Serial.println("LEFT");

      leftMotor.Drive(0);
      rightMotor.Drive(1);
      break;

    case 10074693:
      Serial.println("BACK");

      leftMotor.Drive(-1);
      rightMotor.Drive(-1);
      break;

    case 10031343:
      Serial.println("OK");

      leftMotor.Drive(1);
      rightMotor.Drive(-1);
      break;

    default:
      Serial.println("OTHER BTN");

      leftMotor.Drive(0);
      rightMotor.Drive(0);
  }

  delay(500);
}

void loop()
{
  if (irrecv.decode(&results))

  {
    translateIR();
    irrecv.resume();
  }
}