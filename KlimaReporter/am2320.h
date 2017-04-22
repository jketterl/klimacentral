#ifndef am2320_h
#define am2320_h

#include <Arduino.h>
#include <Wire.h>

class AM2320 {
  public:
    AM2320(TwoWire wire);
    void begin();
    void read();
    float getHumidity();
    float getTemperature();

  private:
    TwoWire _wire;
    // documentation says its 0xb8... but the 7 address bits seem to be misaligned.
    byte _address = 0xB8 >> 1;
    float _temperature;
    float _humidity;
};

#endif
