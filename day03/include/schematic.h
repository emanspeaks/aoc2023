#pragma once

#include <string>
#include <unordered_map>

#include "aoc.h"

#define BLANKCHAR '.'
#define GEARCHAR '*'

typedef std::unordered_map<int, std::vector<int>> GearMap;

class Schematic {
  public:
    Schematic() {m_grid = Grid<char>(BLANKCHAR);}

    void parseLine(const std::string &s);
    int searchGrid(int &gearsum);

    void printGrid() {m_grid.printGrid();}

  private:
    Grid<char> m_grid;
    GearMap m_gearmap;

    int search_perimeter(int x0, int x1, int y);
    void calc_gears(int &gearsum);
};
