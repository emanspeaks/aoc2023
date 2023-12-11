#pragma once

#include <string>

#include "aoc.h"

#define BLANKCHAR '.'
#define STARTCHAR 'S'

enum PipeOpening {
  noopen = 0,
           //lrud
  south  = 0b0001,
  north  = 0b0010,
  east   = 0b0100,
  west   = 0b1000,

  //| is a vertical pipe connecting north and south.
  vert = (north | south),
  //- is a horizontal pipe connecting east and west.
  horiz = (east | west),
  //L is a 90-degree bend connecting north and east.
  ne = (north | east),
  //J is a 90-degree bend connecting north and west.
  nw = (north | west),
  //7 is a 90-degree bend connecting south and west.
  sw = (south | west),
  //F is a 90-degree bend connecting south and east.
  se = (south | east),

  start = -1,
  all = (north | south | east | west)
};

PipeOpening char2open(const char c);
char invertDir(char old);

class PipeMap {
  public:
    void parseLine(const std::string &s);
    int maxDist();
    int enclosedArea();

    void debugGrid();

  private:
    Grid<char> m_grid;
    Coord m_start;
    Grid<bool> m_isloop;

    void inferStart(PipeOpening &last1, PipeOpening &last2);
    Coord getNextPipe(Coord c, PipeOpening &last);
};
