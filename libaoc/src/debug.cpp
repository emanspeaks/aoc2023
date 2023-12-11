#include "debug.h"

std::ofstream *aoc_debug_fp = nullptr;

StrVec &aoc_debug(StrVec &x) {
  #ifdef AOCDEBUG
    for (auto s: x) aoc_debug(s);
  #endif
  return x;
}

void aoc_debug_open() {
  #ifdef AOCDEBUG
    aoc_debug_fp = new std::ofstream();
    aoc_debug_fp->open("aoc_debug.txt");
    std::cout << aoc_debug_fp << "\n";
  #endif
}

void aoc_debug_close(bool openincode) {
  #ifdef AOCDEBUG
    aoc_debug_fp->close();
    delete aoc_debug_fp;
    if (openincode) system("code aoc_debug.txt");
  #endif
}


int aoc_file_test() {
  std::ofstream aoc_test_fp;
  aoc_test_fp.open("aoc_debug.txt");
  aoc_test_fp << "this is a test";
  aoc_test_fp.flush();
  aoc_test_fp.close();
  return 0;
}
