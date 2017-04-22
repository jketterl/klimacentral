#include "am2320.h"

AM2320::AM2320(TwoWire wire) {
  _wire = wire;
}

void AM2320::begin() {
  _wire.setClock(100000);
}

void AM2320::read(){
  _temperature = NAN; _humidity = NAN;
  // wake-up
  _wire.beginTransmission(_address);
  _wire.endTransmission();
  delay(1);

  // write command
  _wire.beginTransmission(_address);
  // read registers
  _wire.write(0x03);
  // start at 0
  _wire.write(0x00);
  // read 4 registers
  _wire.write(0x04);
  _wire.endTransmission();

  delay(1);

  // read command
  _wire.requestFrom(_address, 8);

  // 8 bytes should be provided, but since we don't implement crc we don't care about the last to bytes...
  // TODO implement crc check
  if (_wire.available() < 6) return;

  // first two bytes must contain the command and number of registers, same as requested
  if (_wire.read() != 0x03) return;
  if (_wire.read() != 0x04) return;
  
  _humidity =    ((float) ((_wire.read() << 8) | _wire.read())) / 10;
  _temperature = ((float) ((_wire.read() << 8) | _wire.read())) / 10;
}

float AM2320::getTemperature() {
  return _temperature;
}

float AM2320::getHumidity() {
  return _humidity;
}
