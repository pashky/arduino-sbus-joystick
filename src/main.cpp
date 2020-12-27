#include <Arduino.h>
#include "Joystick.h"
#include "SBUS.h"

Joystick_ Joystick;

SBUS sbus(Serial1);

const unsigned long gcAnalogDelta = 25;
unsigned long gNextTime = 0;

uint16_t t;
uint16_t a;
uint16_t e;
uint16_t r;
uint16_t c5;
uint16_t c6;
uint16_t c7;

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
    t = channels[0];
    a = channels[1];
    e = channels[2];
    r = channels[3];
    c5 = channels[4];
    c6 = channels[5];
    c7 = channels[6];
  }

  // Write priority SBUS channels (TAER) to controller
  Joystick.setXAxis(t);
  Joystick.setYAxis(a);
  Joystick.setRxAxis(e);
  Joystick.setRyAxis(r);

  // Write remaining SBUS channels to controller
  // if (millis() >= gNextTime) {
  //   gNextTime = millis() + gcAnalogDelta;

  //   Joystick.setZAxis(c5);
  //   Joystick.setRzAxis(c6);
  //   Joystick.setButton(0, map(c7, 172, 1811, 0, 1));
  // }
}