class RGBLed
{
  public:
    RGBLed();
    RGBLed(int rPin, int gPin, int bPin, bool commonCathode = false);
    bool setColor(int r, int g, int b, int durationMS = 0);
  private:
    bool setColorTransition(int r, int g, int b, int durationMS);
    bool setLED(int r, int g, int b);    
    bool _commonCathode;
    int _r, _g, _b;
    int _rPin, _gPin, _bPin;
};
