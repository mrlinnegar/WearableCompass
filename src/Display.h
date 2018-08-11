#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

class Display {
 public:
  Display(void);
  void on();
  void off();
  void update(byte number_to_show);

 private:

   

   
};
#endif
