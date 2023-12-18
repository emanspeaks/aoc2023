#pragma once

#include <string>

#include "aoc.h"

// empty space (.), mirrors (/ and \), and splitters (| and -).
#define BLANKCHAR '.'
#define FWDMIRROR '/'
#define BWDMIRROR '\\'
#define VERTSPLIT '|'
#define HORIZSPLIT '-'

class OpticalBench {
  public:
    void parseLine(const std::string &s);
    int initEnergized();
    int maxEnergized();

  private:
    Grid<char> m_bench;

    int propagate(HeadingState init);
};
