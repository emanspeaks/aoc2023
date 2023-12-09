#pragma once

#include <string>

#include "aoc.h"

typedef long long OasisMeas;

class Oasis {
  public:
    void parseLine(const std::string &s);
    OasisMeas extrapolatedSum();
    OasisMeas extrapolatedBackSum();

  private:
    std::vector<std::vector<OasisMeas>> m_rows;
};

OasisMeas extrapolateDiff(std::vector<OasisMeas> &x);
OasisMeas extrapolateBackDiff(std::vector<OasisMeas> &x);
