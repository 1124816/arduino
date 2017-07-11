#include <Servo.h>

Servo myservo;
int sensorValue = 0;
int analogInPin = A0;

void setup() {
  //run once
  myservo.attach(9);  //servo signal pin 9
  myservo.write(127);  //stop servo
}

void loop() {
 sensorValue = analogRead(analogInPin);  //read sensor
 if(sensorValue>890) {  //if coin
 myservo.write(200);  //start moving servo
 delay(555);  //wait
 myservo.write(127);  //stop moving servo
 delay(500);  //wait for noise to die down
 }; 
 delay(2);  //sampling speed
}
