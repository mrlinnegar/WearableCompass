#include "Direction.h"
#define RANGE 22

Direction::Direction(void){
}


// N = 338 to 22
// NE = 23 to 67
// E = 68 to 112
// SE = 113 to 157
// S = 158 to 212
// SW = 213 to 247
// W = 248 to 292
// NW = 293 to 337

// N 1 - NE 2 - E 4 - SE 8 - S 16 - SW 32 - W 64 - NW 128


int Direction::directionToInteger(double direction_in_radians){
  if((direction_in_radians > 360 - RANGE || direction_in_radians <= 0 + RANGE) && (direction_in_radians > 0)) {
    return 1;
  } else if(direction_in_radians >= 45 - RANGE && direction_in_radians < 45 + RANGE) {
    return 2;
  } else if(direction_in_radians >= 90 - RANGE && direction_in_radians < 90 + RANGE) {
    return 4;
  } else if(direction_in_radians >= 135 - RANGE && direction_in_radians < 135 + RANGE) {
    return 8;
  } else if(direction_in_radians >= 180 - RANGE && direction_in_radians < 180 + RANGE) {
    return 16;
  } else if(direction_in_radians >= 225 - RANGE && direction_in_radians < 225 + RANGE) {
    return 32;
  } else if(direction_in_radians >= 270 - RANGE && direction_in_radians < 270 + RANGE) {
    return 64;
  } else if(direction_in_radians >= 315 - RANGE && direction_in_radians < 315 + RANGE) {
    return 128;
  } else {
    return 0;
  }
}
