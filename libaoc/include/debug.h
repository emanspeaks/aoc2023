#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "strings.h"

extern std::ofstream *aoc_debug_fp;

template <typename T> T aoc_debug(T x) {
  #ifdef AOCDEBUG
    std::cout << x << "\n";
    if (aoc_debug_fp && aoc_debug_fp->is_open()) {
      *aoc_debug_fp << x << "\n";
      aoc_debug_fp->flush();
    }
  #endif
  return x;
}

template <typename T> std::vector<T> &aoc_debug(std::vector<T> &x) {
  #ifdef AOCDEBUG
    // std::cout << aoc_debug_fp << "\n";
    std::cout << "<";
    if (aoc_debug_fp && aoc_debug_fp->is_open()) *aoc_debug_fp << "<";
    bool first = true;
    for (auto y: x) {
      if (!first) {
        std::cout << ", ";
        if (aoc_debug_fp && aoc_debug_fp->is_open()) *aoc_debug_fp << ", ";
      } else first = false;
      std::cout << y;
      if (aoc_debug_fp && aoc_debug_fp->is_open()) *aoc_debug_fp << y;
    }
    std::cout << ">\n";
    if (aoc_debug_fp && aoc_debug_fp->is_open()) {
      *aoc_debug_fp << ">\n";
      aoc_debug_fp->flush();
    }
  #endif
  return x;
}

StrVec aoc_debug(StrVec x);

void aoc_debug_open();
void aoc_debug_close(bool openincode = true);

int aoc_file_test();
