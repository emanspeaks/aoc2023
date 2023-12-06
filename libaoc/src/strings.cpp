#include <sstream>

#include "strings.h"

StrVec tokenize_string(const std::string &s, const char delim) {
  std::stringstream sstm(s);
  StrVec svec;
  std::string tmp;
  std::vector<char> x;
  while (std::getline(sstm, tmp, delim)) if (tmp.length()) svec.push_back(tmp);
  return svec;
}

StrDeq tokenize_string_deque(const std::string &s, const char delim) {
  std::stringstream sstm(s);
  StrDeq sdeq;
  std::string tmp;
  std::vector<char> x;
  while (std::getline(sstm, tmp, delim)) if (tmp.length()) sdeq.push_back(tmp);
  return sdeq;
}

const std::string trim_final_char(const std::string &s) {
  return s.substr(0, s.length() - 1);
}

bool is_numeric(const char c) {
  return (c >= '0' && c <= '9');
}
