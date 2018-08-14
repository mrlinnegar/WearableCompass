#include "Display.h"
#include "Arduino.h"
#include <Easing.h>
#define  LATCH_PIN 8
#define  CLOCK_PIN 12
#define  DATA_PIN 11
#define  OUTPUt_ENABLE 3

Display::Display(void){
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(OUTPUt_ENABLE, OUTPUT);
  brightness = 255;
}

void Display::on(){
  setBrightness(128);
  update(255);
}

void Display::off(){
  update(0);
}

void Display::setBrightness(byte brightness){
  analogWrite(OUTPUt_ENABLE, brightness );
}

void Display::update(byte number){
    if(number != Display::number_to_show){
      Display::brightness = 255;
    }
     Display::number_to_show = number;
}

void Display::display(){
  setBrightness((int) Easing::easeInOutQuart(millis() % 1000, 0.0, 255.0, 1000));
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, Display::number_to_show);
  digitalWrite(LATCH_PIN, HIGH);
}
