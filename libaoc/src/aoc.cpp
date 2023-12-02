#include <iostream>
#include <sstream>

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

std::vector<std::string> tokenize_string(const std::string &s) {
  std::stringstream sstm(s);
  std::vector<std::string> svec;
  std::string tmp;
  std::vector<char> x;
  while (std::getline(sstm, tmp, ' ')) svec.push_back(tmp);
  return svec;
}

const std::string trim_final_char(const std::string &s) {
  return s.substr(0, s.length() - 1);
}
