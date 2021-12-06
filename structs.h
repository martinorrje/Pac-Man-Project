#ifndef STRUCTS_H
#define STRUCTS_H

enum Direction{
  Right = 0, 
  Left = 1,
  Up = 2,
  Down = 3
};

struct Coord {
  int x;
  int y;
};

struct Ghost {
  struct Coord pos;
  enum Direction dir;
};

#endif