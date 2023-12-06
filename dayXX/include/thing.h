#pragma once

#include <string>

#include "aoc.h"

class Thing {
  public:
    void parseLine(const std::string &s);

  private:
    int m_x;
};
