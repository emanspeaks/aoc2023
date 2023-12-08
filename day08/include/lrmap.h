#pragma once

#include <string>
#include <unordered_map>

#include "aoc.h"

typedef std::pair<std::string, std::string> LRPair;

class LRMap {
  public:
    void parseLine(const std::string &s);
    int steps();
    long long ghostSteps();

  private:
    std::unordered_map<std::string, LRPair> m_map;
    std::string m_lrstr;

    long long singleGhostPath(std::string start);
};
