#include <sstream>

#include "aoc.h"

StrVec aoc_debug(StrVec x) {
  #ifdef AOCDEBUG
    for (auto s: x) aoc_debug(s);
  #endif
  return x;
}

StrVec tokenize_string(const std::string &s, const char delim) {
  std::stringstream sstm(s);
  StrVec svec;
  std::string tmp;
  std::vector<char> x;
  while (std::getline(sstm, tmp, delim)) if (tmp.length()) svec.push_back(tmp);
  return svec;
}

const std::string trim_final_char(const std::string &s) {
  return s.substr(0, s.length() - 1);
}

bool is_numeric(const char c) {
  return (c >= '0' && c <= '9');
}
