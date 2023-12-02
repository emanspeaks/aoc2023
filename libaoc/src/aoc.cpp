#include <iostream>

#include "aoc.h"

#ifdef AOCDEBUG
  #define aoc_debug_impl(t) aoc_debug_proto(t) {std::cout << x << "\n"; return x;}
  #define aoc_debug_std_impl(t) aoc_debug_std_proto(t) {std::cout << x << "\n"; return x;}
#else
  #define aoc_debug_impl(t) aoc_debug_proto(t) {return x;}
  #define aoc_debug_std_impl(t) aoc_debug_std_proto(t) {return x;}
#endif

aoc_debug_impl(int);
aoc_debug_impl(char);
aoc_debug_impl(double);
aoc_debug_std_impl(string);
