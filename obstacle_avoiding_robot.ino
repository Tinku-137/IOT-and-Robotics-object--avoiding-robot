#include <Servo.h>

// Define pins
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int enA = 6;
const int enB = 7;

// Variables
long duration;
int distance;
Servo myServo;

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Attach servo
  myServo.attach(servoPin);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure distance
  distance = measureDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  // Obstacle avoidance logic
  if (distance < 20) {
    stopRobot();
    delay(500);
    lookAround();
    moveRobot();
  } else {
    moveForward();
  }
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Convert to cm
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 200); // Speed control
  analogWrite(enB, 200);
}

void stopRobot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void lookAround() {
  myServo.write(0); // Look left
  delay(500);
  int leftDistance = measureDistance();
  myServo.write(90); // Look center
  delay(500);
  myServo.write(180); // Look right
  delay(500);
  int rightDistance = measureDistance();
  myServo.write(90); // Return to center

  // Decide direction based on distance
  if (leftDistance > rightDistance) {
    turnLeft();
  } else {
    turnRight();
  }
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500); // Adjust delay for turn angle
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(500); // Adjust delay for turn angle
}
