#pragma once

#include "aocgrid.h"

enum Heading {
  nohead = 0,
          //-yx
  east  = 0b001,
  south = 0b010,
  west  = 0b101,
  north = 0b110,

  px    = 0b001,
  py    = 0b010,
  neg   = 0b100,
  swap  = 0b011,
  all   = 0b111,
};

struct HeadingState {
  Coord xy;
  char head;

  std::string hash() const {return std::to_string(xy[0]) + "," + std::to_string(xy[1]) + "," + std::to_string(head);}
};

Coord getNextCoord(Coord last, char head);
