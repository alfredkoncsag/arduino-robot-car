#include <Arduino.h>
#include "IRremote.h"

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

    int isRun() {
      return true;
    }

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


#define echoPin 2
#define trigPin 3

#define motor1pin1 4
#define motor1pin2 5

#define motor2pin1 6
#define motor2pin2 7

// defines variables
long duration;
int distance;

int receiver = 9;

IRrecv irrecv(receiver);
decode_results results;

Motor leftMotor = Motor(motor1pin2, motor1pin1);
Motor rightMotor = Motor(motor2pin2, motor2pin1);

void setup()
{
  Serial.begin(9600);

  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();

  // Setup ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

    if(distance < 30){
      Serial.println("Danger!!!");
      Serial.println("Stop motors...");
  
      leftMotor.Drive(0);
      rightMotor.Drive(0);
  
      delay(1000);
  
      Serial.println("Turn back the car...");
  
      leftMotor.Drive(1);
      rightMotor.Drive(-1);
  
      delay(300);
  
      Serial.println("Go forrward");
  
      leftMotor.Drive(1);
      rightMotor.Drive(1);
  
  
    }

  if (irrecv.decode(&results))
  {
    translateIR();
    irrecv.resume();
  }
}
