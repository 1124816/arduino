int buttonState = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(11, INPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(9, INPUT); 
  Serial.begin(9600);    
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(11);
  Serial.println(buttonState);
}
