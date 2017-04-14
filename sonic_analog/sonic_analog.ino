
long pulse, inches, cm, pulse2, inches2, cm2;
long total = 0;
long bround[10] = {0}; 
int k = 0;
long total2 = 0;
long bround2[10] = {0}; 
int k2 = 0;
int timer = 0;
int lock = 0;
bool starts = true;



void setup()

{

  Serial.begin(9600);
  pinMode(23, INPUT);
  pinMode(22, INPUT);
  pinMode(21, OUTPUT);
  
}



void loop()
{
  total = 0;
  total2 = 0;
  digitalWrite(21, HIGH);
  pulse = analogRead(23);
  pulse2 = analogRead(22);
  digitalWrite(21, LOW);

  if(k<10) {
    bround[k] = pulse;
    k = k + 1;
  } else {
    k = 0;
    bround[k] = pulse;
    k = k +1;
  };

   if(k2<10) {
    bround2[k2] = pulse2;
    k2 = k2 + 1;
  } else {
    k2 = 0;
    bround2[k2] = pulse2;
    k2 = k2 +1;
  };

  for(int i=0;i<10;i++) {
    total = total + bround[i];
  };
  total = total / 10;

  for(int i=0;i<10;i++) {
    total2 = total2 + bround2[i];
  };
  total2 = total2 / 10;

  if(total*1.5<300&&total2<300&&timer!=0) {
    lock = timer;
    timer = 0;
    starts = false;
  } else if(total*1.5<300&&total2<300) {
    timer = 0;
  } else if(total*1.5<300&&starts) {
    timer += 1;
  } else if(total2<300&&starts) {
    timer += 1;
  } else if(total*1.5>300&&total2>300) {
    timer = 0;
    starts = true;
  };

  //Serial.print(pulse);
  //Serial.print(",");
  //Serial.print(pulse2);
  //Serial.print(",");if
  Serial.print(total*1.5);
  Serial.print(",");
  Serial.print(total2);
  Serial.print(",");
  Serial.print(timer);
  Serial.print(",");
  Serial.println(lock);
  
  
  delay(100);
}

