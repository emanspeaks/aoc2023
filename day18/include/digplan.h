#pragma once

#include <string>

#include "aoc.h"

struct DigInstruction {
  char head;
  int dist;
  unsigned int hexdist;
  char hexhead;
};

class DigPlan {
  public:
    void parseLine(const std::string &s);
    int simpleLagoonArea();

  private:
    Grid<bool> m_grid;
    std::vector<DigInstruction> m_instr;
};
