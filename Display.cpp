#include "Display.h"
#include "Arduino.h"
#define  LATCH_PIN 8
#define  CLOCK_PIN 12
#define  DATA_PIN 11

Display::Display(void){
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}


void Display::update(byte number_to_show){
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, number_to_show);  
  digitalWrite(LATCH_PIN, HIGH);
}
