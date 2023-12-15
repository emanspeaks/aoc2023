#pragma once

#include <string>

#include "aoc.h"

#define CHARSCALAR 17
#define CHARMOD 256
#define DROPCHAR '-'
#define EQUALCHAR '='

class Hasher {
  public:
    void parseLine(const std::string &s);
    int hashInput();
    long long hashMap();

  private:
    StrVec m_initseq;
};

int hashString(std::string s);
