#include <sstream>

#include "aoc.h"

std::vector<std::string> aoc_debug(std::vector<std::string> x) {
  #ifdef AOCDEBUG
    for (auto s: x) aoc_debug(s);
  #endif
  return x;
}

std::vector<std::string> tokenize_string(const std::string &s, const char delim) {
  std::stringstream sstm(s);
  std::vector<std::string> svec;
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
