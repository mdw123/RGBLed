#include "RGBLed.h"

RGBLed::RGBLed()
{
  _r = 0;
  _g = 0;
  _b = 0;
  _rPin = 0;
  _gPin = 0;
  _bPin = 0;
}

RGBLed::RGBLed(int rPin, int gPin, int bPin, bool commonCathode) : RGBLed()
{
  _commonCathode = commonCathode;
  _rPin = rPin;
  _gPin = gPin;
  _bPin = bPin;
  
  pinMode(_rPin, OUTPUT);
  pinMode(_gPin, OUTPUT);
  pinMode(_bPin, OUTPUT);
}

bool RGBLed::setColor(int r, int g, int b, int durationMS)
{
  if(durationMS)
  {
    return setColorTransition(r, g, b, durationMS);
  }
  {
    _r = r;
    _g = g;
    _b = b;
    setLED(r, g, b);
  }
  return false;
}

#define STEPS 50

bool RGBLed::setColorTransition(int r, int g, int b, int durationMS)
{
  int curR = _r * 100;
  int curG = _g * 100;
  int curB = _b * 100;
    
  int stepDuration = durationMS/STEPS;

  int deltaR = ((r * 100) - curR)/STEPS;
  int deltaG = ((g * 100) - curG)/STEPS;
  int deltaB = ((b * 100) - curB)/STEPS;
  
  for(int i = 0; i < STEPS; i++)
  {
    setLED(curR/100, curG/100, curB/100);
    
    curR = curR + deltaR;
    curG = curG + deltaG;
    curB = curB + deltaB;
    delay(stepDuration);
  } 
 
  _r = r;
  _g = g;
  _b = b;
  return setLED(_r, _g, _b);
}

bool RGBLed::setLED(int r, int g, int b)
{
    if(_rPin && _gPin && _bPin)
    {
      if(!_commonCathode)
      { 
        r = 255 - r;
        g = 255 - g;
        b = 255 - b;
      }
  
      analogWrite(_rPin, r); 
      analogWrite(_gPin, g); 
      analogWrite(_bPin, b);
      
      return true;
    }
    return false;
}
