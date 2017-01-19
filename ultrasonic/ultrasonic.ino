const int pwPin = 23;



long pulse, inches, cm;



void setup()

{

  Serial.begin(9600);
  pinMode(pwPin, INPUT);
  
}



void loop()
{
  pulse = pulseIn(pwPin, HIGH);
  inches = pulse / 147;
  cm = inches * 2.54;
  Serial.println(cm);

  delay(500);
}

