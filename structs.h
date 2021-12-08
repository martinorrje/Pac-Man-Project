#ifndef STRUCTS_H
#define STRUCTS_H

enum Direction{
  Right = 0, 
  Left = 1,
  Up = 2,
  Down = 3
};

enum GhostMode{
  Chase,
  Scatter,
  Eaten,
  Frightened
};

struct Coord {
  int x;
  int y;
};

struct Ghost {
  struct Coord pos;
  struct Coord scatterTarget;
  struct Coord target;
  enum Direction dir;
  enum GhostMode ghostMode;
};

#endif