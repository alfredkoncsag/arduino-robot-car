#include <Servo.h> //Servo motor library
#include <IRremote.h>

//servo pin
#define servoPin 8

const int LeftForward = 4; // L298N control pins
const int LeftBackward = 5;
const int RightForward = 6;
const int RightBackward = 7;

const int IRreceiver = 9;

IRrecv irrecv(IRreceiver);
decode_results results;

#define trigPin A1 //sensor pins - analog input 1
#define echoPin A2 //analog input 2
#define maximum_distance 200

boolean goesForward = false;

long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

int program;

Servo servo_motor; //servo name

void setup()
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();

  pinMode(trigPin, OUTPUT);                         // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);                          // Sets the echoPin as an INPUT
  Serial.begin(9600);                               // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor

  pinMode(RightForward, OUTPUT);
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBackward, OUTPUT);
  pinMode(RightBackward, OUTPUT);
  servo_motor.attach(servoPin); //servo pin
  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop()
{

  if (irrecv.decode(&results))
  {
    Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
    translateIR();
    irrecv.resume();
  }

  if (program == 1)
  {
    int distanceRight = 0;
    int distanceLeft = 0;
    delay(50);
    if (distance <= 20)
    {
      moveStop(); // obstacle probably on the route forward, so stop
      delay(300);
      moveBackward();
      delay(400);
      moveStop();
      delay(300);
      distanceRight = lookRight();
      delay(300);
      distanceLeft = lookLeft();
      delay(300);
      if (distance >= distanceLeft)
      {
        turnRight(); // calculate in which direction the obstacle is more far
        moveStop();
      }
      else
      {
        turnLeft();
        moveStop();
      }
    }
    else
    {
      moveForward();
    }
    distance = readPing();
  }
}

void translateIR()
{

  switch (results.value)
  {
  case 10063983:
    Serial.println("PROGRAM AUTOMAT");
    program = 1;
    break;
  case 10041543:
    Serial.println("EXIT");
    program = 0;
    moveStop();
    break;

  case 0xFFFFFFFF:
    Serial.println(" REPEAT");
    break;
  default:

    Serial.println(results.value);
  }

  delay(500);
}

int lookRight()
{
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft()
{
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing()
{
  delay(70);

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int cm = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (cm == 0)
  {
    cm = 250;
  }

  return cm;
}

void moveStop()
{
  digitalWrite(RightForward, LOW);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightBackward, LOW);
  digitalWrite(LeftBackward, LOW);
}

void moveForward()
{
  if (!goesForward)
  {
    goesForward = true;
    digitalWrite(LeftForward, HIGH);
    digitalWrite(RightForward, HIGH);
    digitalWrite(LeftBackward, LOW);
    digitalWrite(RightBackward, LOW);
  }
}

void moveBackward()
{
  goesForward = false;
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightBackward, HIGH);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightForward, LOW);
}

void turnRight()
{
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightBackward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightForward, LOW);
  delay(300);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightBackward, LOW);
}

void turnLeft()
{
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftForward, LOW);
  digitalWrite(RightBackward, LOW);
  delay(300);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(RightForward, HIGH);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightBackward, LOW);
}