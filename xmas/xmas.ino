
#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;
uint16_t x = 0;
uint16_t y = 8;
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
    if(i == x) {
      colors[i] = (rgb_color){ 255, 0, 0 };
    } else if(abs(x-i == 1)){
      colors[i] = (rgb_color){ 100, 0, 0 };
    } else if(i == y) {
      colors[i] = (rgb_color){ 0, 255, 0 };
    } else if(abs(y-i == 1)){
      colors[i] = (rgb_color){ 0, 100, 0 };
    } else {
      colors[i] = (rgb_color){ 0, 0, 0 };
    };
  }
  

  ledStrip.write(colors, LED_COUNT);
  if(y>41) {
    y = 0;
  } else if (x>41) {
    x = 0;
  }else{    
    x = x + 1;
    y = y + 1;
  }
  delay(140);
} 
