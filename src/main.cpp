#include <Arduino.h>
#include "Joystick.h"
#include "SBUS.h"

Joystick_ Joystick;

SBUS sbus(Serial1);

uint16_t channels[16];
bool failSafe;
bool lostFrame;

void setup() {
  // Set Range Values
  Joystick.setXAxisRange(172, 1811);
  Joystick.setYAxisRange(172, 1811);
  Joystick.setRxAxisRange(172, 1811);
  Joystick.setRyAxisRange(172, 1811);
  Joystick.setZAxisRange(172, 1811);
  Joystick.setRzAxisRange(172, 1811);

  sbus.begin();

  Joystick.begin(true);
}

void loop() {
  if(sbus.read(&channels[0], &failSafe, &lostFrame)) {
    Joystick.setXAxis(channels[0]);
    Joystick.setYAxis(channels[1]);
    Joystick.setRxAxis(channels[2]);
    Joystick.setRyAxis(channels[3]);
//    Joystick.setZAxis(channel[4]);
//    Joystick.setRzAxis(channel[5]);
  }
}