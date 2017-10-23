#include <Servo.h>

Servo myservo;
int sensorValue = 0;
int analogInPin = A0;

void setup() {
    Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //run once
  myservo.attach(9);  //servo signal pin 9
  myservo.write(127);  //stop servo
  // the setup function runs once when you press reset or power the board
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}
  


void loop() {
 sensorValue = analogRead(analogInPin);  //read sensor
 Serial.println(sensorValue);
 if(sensorValue>900) {  //if coin is dropped
 Serial.print("yes");
 
 myservo.write(273);  //start moving servo
 delay(1190);  //wait for servo to move
 myservo.write(127);  //stop moving servo
 delay(500);  //wait for noise to die down
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for two seconds
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW;  
 }; 
 delay(2);  //sampling speed
}
