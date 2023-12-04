#include "debug.h"

StrVec aoc_debug(StrVec x) {
  #ifdef AOCDEBUG
    for (auto s: x) aoc_debug(s);
  #endif
  return x;
}
