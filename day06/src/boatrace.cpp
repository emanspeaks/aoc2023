#include "boatrace.h"

void RaceRecordSet::parseLine(const std::string &s) {
  static bool istime = true;
  std::vector<long> &tgt = (istime)? m_time : m_dist;
  long long &bigtgt = (istime)? m_bigtime : m_bigdist;
  istime = false;
  StrVec svec = tokenize_string(s);
  for (auto x: svec) if (is_numeric(x[0])) tgt.push_back(std::stoi(x));
  aoc_debug(tgt);

  std::string bigstr;
  for (auto c: s) if (is_numeric(c)) bigstr += c;
  bigtgt = std::stoll(bigstr);
  aoc_debug(bigtgt);
}

long long RaceRecordSet::distFunc(long long maxtime, long long button) {
  return (maxtime - button)*button;
}

long RaceRecordSet::winProduct() {
  long prod = 1;
  long long rundist;
  int wins;
  for (int i = 0; i < m_time.size(); i++) {
    wins = 0;
    for (int button = 1; button < m_time[i]; button++) {
      rundist = distFunc(m_time[i], button);
      if (rundist > m_dist[i]) wins++;
    }
    if (wins) prod *= wins;
  }
  return prod;
}

long RaceRecordSet::winBigCount() {
  long long rundist, button = 0, leftbutton = -1, rightbutton = -1;
  long wins = -1;

  while (leftbutton < 0) {
    rundist = distFunc(m_bigtime, ++button);
    if (rundist > m_bigdist) leftbutton = button;
  }

  button = m_bigtime;
  while (rightbutton < 0) {
    rundist = distFunc(m_bigtime, --button);
    if (rundist > m_bigdist) rightbutton = button;
  }

  return rightbutton - leftbutton + 1;
}
