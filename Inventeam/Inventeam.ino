


long pulse, inches, cm;
long total = 0;
long bround[10] = {0}; 
int k = 0;
int light = 0;



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
  
  if(k<10) {
    bround[k] = cm;
    k = k + 1;
  } else {
    k = 0;
    bround[k] = cm;
    k = k +1;
  };

  for(int i=0;i<10;i++) {
     total = total + bround[i];
  };
  total = total / 10;

  if(light != 0) {
    if(light%2==0) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    };
    light = light -1;
  }else if(total<150) {
    digitalWrite(13, HIGH); 
    light = 40; 
  }else{
    digitalWrite(13, LOW);  
  };
  Serial.print(cm);
  Serial.print(",");
  Serial.println(total);
  delay(100);
}

