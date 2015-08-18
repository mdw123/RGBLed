# RGBLed
arduino RGB LED library

## Sample


```
#include "RGBLed.h"

RGBLed * pLed = NULL;
  
void setup() 
{
  pLed = new RGBLed(9, 6, 5);  
  Serial.begin(9600);
}

void loop() {  
  pLed->setColor(255, 0, 0, 500); // red 
  delay(1000);
  pLed->setColor(0, 255, 0, 500); // green 
  delay(1000);
  pLed->setColor(0, 0, 255, 500); // blue 
  delay(1000);
  pLed->setColor(255, 255, 0, 500); // yellow 
  delay(1000);
  pLed->setColor(80, 0, 80, 500); // purple 
  delay(1000);
  pLed->setColor(0, 255, 255, 500); // aqua 
  delay(1000);
  pLed->setColor(0, 0, 0, 500); // off 
  delay(1000);
}
```


