#pragma once

#include <string>

#include "aoc.h"

class RaceRecordSet {
  public:
    void parseLine(const std::string &s);
    long winProduct();
    long winBigCount();

  private:
    std::vector<long> m_time, m_dist;
    long long m_bigtime, m_bigdist;
    long long distFunc(long long maxtime, long long button);
};
