#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <deque>

#include "strings.h"

extern std::ofstream *aoc_debug_fp;

template <typename T> const T aoc_debug(const T x, bool newline = true) {
  #ifdef AOCDEBUG
    std::cout << x;
    if (newline) std::cout << "\n";
    if (aoc_debug_fp && aoc_debug_fp->is_open()) {
      *aoc_debug_fp << x;
      if (newline) {
        *aoc_debug_fp << "\n";
        aoc_debug_fp->flush();
      }
    }
  #endif
  return x;
}

template <typename T> const std::vector<T> &aoc_debug(const std::vector<T> &x, bool newline = true) {
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
      aoc_debug(y, false);
    }
    if (newline) {
    std::cout << ">\n";
      if (aoc_debug_fp && aoc_debug_fp->is_open()) {
        *aoc_debug_fp << ">\n";
        aoc_debug_fp->flush();
      }
    }
  #endif
  return x;
}

template <typename T, int N> const std::array<T, N> &aoc_debug(const std::array<T, N> &x, bool newline = true) {
  #ifdef AOCDEBUG
    // std::cout << aoc_debug_fp << "\n";
    std::cout << "(";
    if (aoc_debug_fp && aoc_debug_fp->is_open()) *aoc_debug_fp << "(";
    bool first = true;
    for (auto y: x) {
      if (!first) {
        std::cout << ", ";
        if (aoc_debug_fp && aoc_debug_fp->is_open()) *aoc_debug_fp << ", ";
      } else first = false;
      aoc_debug(y, false);
    }
    if (newline) {
    std::cout << ")\n";
      if (aoc_debug_fp && aoc_debug_fp->is_open()) {
        *aoc_debug_fp << ")\n";
        aoc_debug_fp->flush();
      }
    }
  #endif
  return x;
}

template <typename T> const std::deque<T> &aoc_debug(const std::deque<T> &x, bool newline = true) {
  #ifdef AOCDEBUG
    // std::cout << aoc_debug_fp << "\n";
    std::cout << "[";
    if (aoc_debug_fp && aoc_debug_fp->is_open()) *aoc_debug_fp << "[";
    bool first = true;
    for (auto y: x) {
      if (!first) {
        std::cout << ", ";
        if (aoc_debug_fp && aoc_debug_fp->is_open()) *aoc_debug_fp << ", ";
      } else first = false;
      aoc_debug(y, false);
    }
    if (newline) {
    std::cout << "]\n";
      if (aoc_debug_fp && aoc_debug_fp->is_open()) {
        *aoc_debug_fp << "]\n";
        aoc_debug_fp->flush();
      }
    }
  #endif
  return x;
}

const StrVec &aoc_debug(const StrVec &x);

void aoc_debug_open();
void aoc_debug_close(bool openincode = true);

int aoc_file_test();
