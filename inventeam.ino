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
int starts = 0;

void setup()

{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(6, OUTPUT);   //sync pin for sensors
  pinMode(7, OUTPUT);    //led

}



void loop()
{
  total = 0;
  total2 = 0;
  digitalWrite(6, HIGH);
  pulse = analogRead(A0)*.52;  //cal math
  pulse2 = analogRead(A2)*.52-4;
  digitalWrite(6, LOW);

  if(k<15) {  //averaging
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

  if(state==0){  //one time reset
    state = 1;
    timer = 0;
    low = 900;
    low2 = 900;
    dir = 0;
  } else if(state==1){ //loop wait for trigger
    if(starts < 15) {
      starts = starts + 1;
    };
    if(total<120&&starts == 15){
      state = 2;
      dir = 1;
    } else if(total2<120&&starts == 15) {
       state = 2;
       dir = 2;
    };
  } else if(state==2){   //one time sensor triggered
    timer = 1;
    //direction
    digitalWrite(7, HIGH);
    state = 3;
  } else if(state==3){   //loop wait to pass and record lowest point
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
  } else if(state==4){  //one time bike past
    digitalWrite(7, LOW);
    times = timer;
    speeds = (low+low2)/2;
    speeds = sqrt(sq(speeds)*2);
    speeds = speeds/(times/5);
    Serial.print("bob");

    EEPROM.write(combined, dir);
    EEPROM.write(combined, times);
    EEPROM.write(combined, Time.now());

    state = 5;
  } else if(state==5){  //loop wait for values to return to normal
    if(total>120&&total2>120){
      state = 0;
    };
  };


  delay(100);
} 
