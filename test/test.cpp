#include <stdio.h>
#include <math.h>

// N = 338 to 22 = 22
// NE = 23 to 67 = 67
// E = 68 to 112 = 112
// SE = 113 to 157 = 157
// S = 158 to 212 = 212
// SW = 213 to 247 = 247
// W = 248 to 292 = 292
// NW = 293 to 337 = 337

// N 1 - NE 2 - E 3 - SE 4 - S 5 - SW 6 - W 7 - NW 8

int RANGE = 22;

int directionToInteger(double direction) {
  if((direction > 360 - RANGE || direction <= 0 + RANGE) && (direction > 0)) {
    return 1;
  } else if(direction >= 45 - RANGE && direction < 45 + RANGE) {
    return 2;
  } else if(direction >= 90 - RANGE && direction < 90 + RANGE) {
    return 4;
  } else if(direction >= 135 - RANGE && direction < 135 + RANGE) {
    return 8;
  } else if(direction >= 158 && direction < 212) {
    return 16;
  } else if(direction >= 213 && direction < 247) {
    return 32;
  } else if(direction >= 248 && direction < 292) {
    return 64;
  } else if(direction >= 293 && direction < 337) {
    return 128;
  } else {
    return 0;
  }
}

int main() {
  int num = directionToInteger(339);
  printf("%d\n", num);

  num = directionToInteger(22);
  printf("%d\n", num);

  num = directionToInteger(23);
  printf("%d\n", num);

  num = directionToInteger(66);
  printf("%d\n", num);

  num = directionToInteger(265.345);
  printf("%d\n", num);

  return 0;
}
