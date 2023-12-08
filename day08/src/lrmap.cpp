#include <numeric>

#include "lrmap.h"

void LRMap::parseLine(const std::string &s) {
  static bool first = true;
  if (first) {m_lrstr = s; first = false;}
  else {
    StrVec svec = tokenize_string(s);
    m_map[svec[0]] = LRPair(svec[2].substr(1, svec[2].length() - 2), svec[3].substr(0, svec[3].length() - 1));
  }
}

int LRMap::steps() {
  int s = 0, i = 0;
  std::string cur = "AAA";
  while (cur != "ZZZ") {
    cur = (m_lrstr[i++] == 'L')? m_map[cur].first : m_map[cur].second;
    if (i == m_lrstr.length()) i = 0;
    s++;
  }
  return s;
}

long long LRMap::singleGhostPath(std::string start) {
  long long s = 0;
  int i = 0;
  std::string cur = start;
  while (cur.back() != 'Z') {
    cur = (m_lrstr[i++] == 'L')? m_map[cur].first : m_map[cur].second;
    if (i == m_lrstr.length()) i = 0;
    s++;
  }
  return s;
}

long long LRMap::ghostSteps() {
  /* // the brute force method
  long s = 0;
  StrVec cur;
  char c;
  int i = 0;
  for (auto& [k, v]: m_map) if (k.back() == 'A') cur.push_back(k);
  bool nonz = true;
  std::string next;
  while (nonz) {
    nonz = false;
    c = m_lrstr[i++];
    for (int j = 0; j < cur.size(); j++) {
      next = (c == 'L')? m_map[cur[j]].first : m_map[cur[j]].second;
      cur[j] = next;
      if (next.back() != 'Z') nonz = true;
    }
    if (i == m_lrstr.length()) i = 0;
    s++;
    if (!(s % 100000)) aoc_debug(steps);
  }
  */

  // what about as an LCM problem?
  std::vector<int> svec;
  long long s = 1;
  for (auto& [k, v]: m_map) if (k.back() == 'A') s = std::lcm<long long, long long>(s, singleGhostPath(k));
  return s;
}
