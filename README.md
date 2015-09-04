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
}


void loop() {
    while (Serial.available() > 0) {
      // look for the next valid integer in the incoming serial stream:
      int red = Serial.parseInt(); 
      // do it again:
      int green = Serial.parseInt(); 
      // do it again:
      int blue = Serial.parseInt(); 

      // look for the newline. That's the end of your
      // sentence:
      if (Serial.read() == '\n') {
        // constrain the values to 0 - 255 and invert
        // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
        red = constrain(red, 0, 255);
        green = constrain(green, 0, 255);
        blue = constrain(blue, 0, 255);
        // https://www.arduino.cc/en/Tutorial/ReadASCIIString
        pLed->setColor(red, green, blue, 500);
      }
  }

}
```


#and a bit of python to get you going via http
```
#!/usr/bin/env python
#
import serial
import logging
import json
from time import sleep
from flask import Flask

from logging.handlers import RotatingFileHandler

app = Flask(__name__)
currcolor = None

ser = serial.Serial('/dev/cu.Repleo-CH341-00001114', timeout=5)
connected = False
currentcolor = None

@app.route("/")
def index():
  return "led server is go"

@app.route('/color/<color_set>', methods=['POST'])
def set_color(color_set=None):
  app.logger.debug("color is {0}".format(color_set))
  for i in range(1,3):
    errored = False
    app.logger.debug("range is {0}".format(i))
    cool_story_bro = color_set + "\n"
    try:
      ser.write(str(cool_story_bro))
    except Exception as e:
      errored = True
      print("ERR ser.write: %s" % (e))
    if errored is not True:
      break
    sleep(2)
  retinfo = {}
  retinfo['color'] = color_set
  return(json.dumps(retinfo))

if __name__ == "__main__":
  while not connected:
    serin = ser.read()
    connected = True
  # just go ahead and read anything that is already on the serial port ( which 
  # SHOULD be nothing, but it's serial. so there's that. 
  ser.readline(13)
  handler = RotatingFileHandler('server.log', maxBytes=10000, backupCount=1)
  handler.setLevel(logging.DEBUG)
  app.logger.addHandler(handler)
  app.run()
```
