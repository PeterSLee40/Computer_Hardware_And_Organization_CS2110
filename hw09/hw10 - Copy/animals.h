#include <stdint.h>
//#include "geometry.h"
struct Monster1 {
  int x;
  int y;
  int attack;
  int frequency;
  int health;
  Image* image;
};

struct Human {
  int x;
  int y;
  int attack;
  int frequency;
  int health;
  int armor;
  Image* image;
};
struct Arrow {
  int x;
  int y;
  int dx;
  int dy;
  int attack;
  Image* image;
};
