
#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;
uint16_t x = 0;
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
    }else{
      colors[i] = (rgb_color){ 0, 0, 0 };
    };
  }
  

  ledStrip.write(colors, LED_COUNT);
  if(x<42) {
    x = x + 1;
  }else{
    x = 0;
  }
  delay(265);
}
