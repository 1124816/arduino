


long pulse, inches, cm;
long total = 0;
long bround[5] = {0}; 
int k = 0;



void setup()

{

  Serial.begin(9600);
  pinMode(23, INPUT);
  pinMode(13, OUTPUT);
  
}



void loop()
{
  total = 0;
  pulse = pulseIn(23, HIGH);
  inches = pulse / 147;
  cm = inches * 2.54;
  
  if(k<5) {
    bround[k] = cm;
    k = k + 1;
  } else {
    k = 0;
    bround[k] = cm;
    k = k +1;
  };

  for(int i=0;i<5;i++) {
     total = total + bround[i];
  };
  total = total / 5;
  
  if(total<150) {
    digitalWrite(13, HIGH);  
  }else{
    digitalWrite(13, LOW);  
  };
  Serial.print(cm);
  Serial.print(",");
  Serial.println(total);
  delay(500);
}

