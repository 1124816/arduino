#include <OneWire.h>

OneWire ds(2);

String inputString = "";  //holds command
boolean newline = false;  //if command has been entered
boolean led = false;  //whether the heater is on or off
boolean leds = true;  //whether theater is in manual(off) or auto

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  pinMode(13, OUTPUT);
}

void loop() {
  if (newline) {
    //if command entered
    Serial.println(inputString);
    if (leds) {
      //set to off
      Serial.println("man");
      leds = false;
    }else{
      //set to auto
      Serial.println("auto");
      leds = true;
    };
    // clear the string:
    inputString = "";
    newline = false;
  }

  //copy/paste from sensor example begins

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

  //copy/paste from sensor example ends

  if(leds) {
    //if the heater is set to auto
    if(celsius < 2 && !led){
      //if off and cold turn on
      digitalWrite(13, HIGH);
      led = true;
      Serial.println("turning on auto");
    } else if(celsius > 2 && led) {
      //if on and hot turn off
      digitalWrite(13, LOW);
      led = false;
      Serial.println("turning off auto");
      }
  }else{
    //if the heater is set to manual
    if(led) {
      //if on and manually set to off turn off
      digitalWrite(13, LOW);
      led = false;
      Serial.println("turning off");
    }
  }
}

void serialEvent() {
  //when command is sent
  while (Serial.available()) {
    char com = (char)Serial.read();
    inputString += com;
    if (com == '\n') {
      newline = true;
    }
  }
}
