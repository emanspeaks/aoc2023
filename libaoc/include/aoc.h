#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "aocgrid.h"

#define CAT(a, b) a##b

typedef std::vector<std::string> StrVec;

const int inf = std::numeric_limits<int>::max();

template <typename T> T aoc_debug(T x) {
  #ifdef AOCDEBUG
    std::cout << x << "\n";
  #endif
  return x;
}

template <typename T> std::vector<T> aoc_debug(std::vector<T> x) {
  #ifdef AOCDEBUG
    std::cout << "<";
    bool first = true;
    for (auto y: x) {
      if (!first) std::cout << ", "; else first = false;
      std::cout << y;
    }
    std::cout << ">\n";
  #endif
  return x;
}

StrVec aoc_debug(StrVec x);

StrVec tokenize_string(const std::string &s, const char delim = ' ');
const std::string trim_final_char(const std::string &s);
bool is_numeric(const char c);
