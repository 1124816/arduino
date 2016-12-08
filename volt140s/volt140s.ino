
#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;
uint16_t x = 42;
// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

void setup()
{
}

void loop()
{
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    if(i== x) {
      colors[i] = (rgb_color){ 0, 255, 255 };
    } else if(abs(x-i == 1)){
      colors[i] = (rgb_color){ 0, 100, 100 };
    } else if(x>78&&i<10){
      colors[i] = (rgb_color){ 0, 0, 100 };
    } else if(x>72&&i<10){
      colors[i] = (rgb_color){ 0, 0, 0 };
    } else if(x>66&&i<10){
      colors[i] = (rgb_color){ 100, 0, 0 };
    } else if(x>60&&i<10){
      colors[i] = (rgb_color){ 0, 0, 0 };
    } else if(x>54&&i<10){
      colors[i] = (rgb_color){ 100, 0, 0 };
    } else if(x>48&&i<10){
      colors[i] = (rgb_color){ 0, 0, 0 };
    } else if(x>42&&i<10){
      colors[i] = (rgb_color){ 100, 0, 0 };
    }else{
      colors[i] = (rgb_color){ 0, 0, 0 };
    };
  }
  

  ledStrip.write(colors, LED_COUNT);
  if(x<84) {
    x = x + 1;
  }else{
    x = 0;
  }
  delay(140);
}
