
long pulse, inches, cm, pulse2, inches2, cm2;
long total = 0;
long bround[15] = {0}; 
int k = 0;
long total2 = 0;
long bround2[15] = {0}; 
int k2 = 0;
int timer = 0;
int state = 1;
int times = 0;
float low = 900;
float low2 = 900;
float speeds = 0;
int dir = 0;

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
  pulse = analogRead(23)*.52;
  pulse2 = analogRead(22)*.52-4;
  digitalWrite(21, LOW);

  if(k<15) {
    bround[k] = pulse;
    k = k + 1;
  } else {
    k = 0;
    bround[k] = pulse;
    k = k +1;
  };

   if(k2<15) {
    bround2[k2] = pulse2;
    k2 = k2 + 1;
  } else {
    k2 = 0;
    bround2[k2] = pulse2;
    k2 = k2 +1;
  };

  for(int i=0;i<15;i++) {
    total = total + bround[i];
  };
  total = total / 15;

  for(int i=0;i<15;i++) {
    total2 = total2 + bround2[i];
  };
  total2 = total2 / 15;

  if(state==0){
    state = 1;
    timer = 0;
    low = 900;
    low2 = 900;
    dir = 0;
  } else if(state==1){
    if(total<120){
      state = 2;  
      dir = 1;
    } else if(total2<120) {
       state = 2;  
       dir = 2;
    };
  } else if(state==2){
    timer = 1;
    //direction
    state = 3;
  } else if(state==3){
    timer +=1;
    if(pulse<low) {
      low = total;
    };
    if(pulse2<low2) {
      low2 = total;
    };
    if(total<120&&dir ==2){
      state = 4;  
    } else if(total2<120&&dir ==1) {
      state = 4;  
    };
  } else if(state==4){
    times = timer;
    speeds = (low+low2)/2;
    speeds = sqrt(sq(speeds)*2);
    speeds = speeds/(times/5);
    state = 5;
  } else if(state==5){
    if(total>120&&total2>120){
      state = 0;  
    };
  };

  //Serial.print(pulse);
  //Serial.print(",");
  //Serial.print(pulse2);
  //Serial.print(",");if
  Serial.print(total);
  Serial.print(",");
  Serial.print(total2);
  Serial.print(",");
  Serial.print(timer);
  Serial.print(",");
  Serial.println(speeds);
  
  
  delay(100);
}

