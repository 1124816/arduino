

#include <OneWire.h>

OneWire  ds(2); 

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean led = false;
boolean leds = true;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(13, OUTPUT); 
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if (leds) {
      //digitalWrite(13, LOW);
      Serial.println("man");
      leds = false;
    }else{
      //digitalWrite(13, HIGH);
      Serial.println("auto");
      //led = true;
      leds = true;
    }; 
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

    byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }
  

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      type_s = 1;
      break;
    case 0x28:
      type_s = 0;
      break;
    case 0x22:
      type_s = 0;
      break;
    default:
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        
  
  delay(1000);     
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);        

  for ( i = 0; i < 9; i++) {           
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; 
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  
    else if (cfg == 0x20) raw = raw & ~3; 
    else if (cfg == 0x40) raw = raw & ~1; 
  }
  celsius = (float)raw / 16.0;
  Serial.println(celsius);
  if(leds) {
    if(celsius < 2 && !led){
      digitalWrite(13, HIGH);
      led = true;
      Serial.println("turning on auto");
    } else if(celsius > 2 && led) {
      digitalWrite(13, LOW);
      led = false;
      Serial.println("turning off auto");
      }
  }else{
    if(led) {
      digitalWrite(13, LOW);
      led = false;
      Serial.println("turning off");
    }
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


