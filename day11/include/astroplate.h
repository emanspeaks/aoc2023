#pragma once

#include <string>

#include "aoc.h"

#define BLANKCHAR '.'
#define GALAXYCHAR '#'
#define BLANKSCALAR 1000000

class AstroPlate {
  public:
    // AstroPlate(): m_plate(Grid<char>(BLANKCHAR)) {}

    void parseLine(const std::string &s);
    void expandCols();
    long long totalMinDist(int scalar = 2);

    void debugGrid() {m_plate.debugGrid();}

  private:
    Grid<bool> m_plate;
    std::vector<Coord> m_coords;
    std::vector<int> m_blankrow, m_blankcol;
};
