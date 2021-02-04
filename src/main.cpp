#include <Arduino.h>

#include <Servo.h>
#include "IRremote.h"

class CarMotor
{

private:
  int directionPin1;
  int directionPin2;

public:
  //Method to define the motor pins
  CarMotor(int dPin1, int dPin2)
  {
    directionPin1 = dPin1;
    directionPin2 = dPin2;
  };

  int isRun()
  {
    return digitalRead(directionPin1) + digitalRead(directionPin2) != 0;
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

// Ultrasonic sendor pins
#define echoPin 2
#define trigPin 3

//left motor pins
#define motor1pin1 4
#define motor1pin2 5

//right motor pins
#define motor2pin1 6
#define motor2pin2 7

//servo pin
#define servoPin 8

//IR reciver pin
#define receiver 9

// defines variables
long duration;
int distance;
int pos = 0; // variable to store the servo position

IRrecv irrecv(receiver);
decode_results results;

CarMotor leftMotor = CarMotor(motor1pin2, motor1pin1);
CarMotor rightMotor = CarMotor(motor2pin2, motor2pin1);

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup()
{
  Serial.begin(9600);

  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();

  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object

  // Setup ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Set initial motor pins
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
    Serial.println(results.value);
  }

  delay(500);
}

void calcDistance()
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
}

void loop()
{

  calcDistance();

  Serial.println(leftMotor.isRun());
  Serial.println(rightMotor.isRun());

  if (distance < 20)
  {
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
  //  if (distance < 20) {
  //    Serial.println("Danger!!!");
  //    Serial.println("Stop motors...");
  //
  //    leftMotor.Drive(0);
  //    rightMotor.Drive(0);
  //
  //    Serial.println("Map location...");
  //
  //    int maxPos = 0;Q
  //    int max = 0;
  //
  //    for (pos = 0; pos <= 180; pos += 1) {
  //      // in steps of 1 degree
  //      myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //      delay(15);                       // waits 15ms for the servo to reach the position
  //      calcDistance();
  //
  //      if (distance > max) {
  //        max = distance;
  //        maxPos = pos;
  //      }
  //    }
  //
  //    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //      myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //      delay(15);                       // waits 15ms for the servo to reach the position
  //      calcDistance();
  //      if (distance > max) {
  //        max = distance;
  //        maxPos = pos;
  //      }
  //    }
  //
  //    myservo.write(maxPos);              // tell servo to go to position in variable 'pos'
  //    delay(1000);                       // waits 15ms for the servo to reach the position
  //    Serial.println("MAX");
  //    Serial.println(max);
  //    Serial.println(maxPos);
  //  }

  if (irrecv.decode(&results))
  {
    translateIR();
    irrecv.resume();
  }
}
