#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

class Display {
 public:
  Display(void);
  void on();
  void off();
  void update(byte number_to_show);
  void display();
  void setBrightness(byte brightness);

 private:
  byte number_to_show;
  byte brightness;
  unsigned long last_update;
  boolean state;
};
#endif
