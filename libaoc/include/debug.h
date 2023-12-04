#pragma once

#include <iostream>
#include <vector>

#include "strings.h"

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
