
long pulse, inches, cm, pulse2, inches2, cm2;




void setup()

{

  Serial.begin(9600);
  pinMode(23, INPUT);
  pinMode(22, INPUT);
  pinMode(21, OUTPUT);
  
}



void loop()
{
  digitalWrite(21, HIGH);
  pulse = pulseIn(23, HIGH);
  inches = pulse / 147;
  cm = inches * 2.54;
  pulse2 = pulseIn(22, HIGH);
  inches2 = pulse2 / 147;
  cm2 = inches2 * 2.54;
  digitalWrite(21, LOW);

  Serial.print(cm);
  Serial.print(",");
  Serial.println(cm2);
  
  delay(200);
}

