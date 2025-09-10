// C++ code
//
#include <Servo.h>

int UltrasonicSensor = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_2;

void setup()
{
  Serial.begin(9600);
  servo_2.attach(2, 500, 2500);
}

void loop()
{
  UltrasonicSensor = 0.01723 * readUltrasonicDistance(7, 6);
  Serial.println(UltrasonicSensor);
  if (UltrasonicSensor <= 80) {
    servo_2.write(90);
  } else {
    servo_2.write(0);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
