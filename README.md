# RGBLed
arduino RGB LED library

## Sample


```
#include "RGBLed.h"
#include "Arduino.h"

RGBLed * pLed = NULL;
String inputString = ""; // to hold incoming data
boolean stringComplete = false; //done or not

void setup()
{
  // On my nano, the Dx lined up directly to these pin values
  pLed = new RGBLed(3, 5, 6);
  Serial.begin(9600);
  // reserve 200bytes
  inputString.reserve(200);
}


void loop() {
    if (stringComplete) {
      Serial.println(inputString);
      if (inputString == "r\n" ) {
        pLed->setColor(255, 0, 0, 500); // red
      } else {
        pLed->setColor(0, 255, 0, 500); // green
      } /*
        pLed->setColor(0, 0, 255, 500); // blue
        pLed->setColor(255, 255, 0, 500); // yellow
        pLed->setColor(80, 0, 80, 500); // purple
        pLed->setColor(0, 255, 255, 500); // aqua
        pLed->setColor(0, 0, 0, 500); // off
        */
      inputString = "";
      stringComplete = false;
    }
}

void serialEvent() {
   while (Serial.available()) {
    // read incoming serial data
    char inChar = (char)Serial.read();
    inputString += inChar;
    // if newline, set a flag so the main loop can do something about it
    if (inChar == '\n') {
      stringComplete = true;
    }
   }
}
```

# use stty to set the device to 9600 baud
```
shell$ stty -f /dev/cu.Repleo-CH341-00001114 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts

# turn red
shell$ echo "r" > /dev/cu.Repleo-CH341-00001114
# turn another color ( like green )
shell$ echo "what" > /dev/cu.Repleo-CH341-00001114
```
