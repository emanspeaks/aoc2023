#include <numeric>

#include "oasis.h"

void Oasis::parseLine(const std::string &s) {
  std::vector<OasisMeas> row;
  StrVec svec = tokenize_string(s);
  for (auto x: svec) row.push_back(std::stoll(x));
  m_rows.push_back(row);
}

OasisMeas Oasis::extrapolatedSum() {
  OasisMeas sum = 0;
  for (auto row: m_rows) {
    sum += extrapolateDiff(aoc_debug(row));
    aoc_debug(sum);
    aoc_debug("");
    continue;
  }
  return sum;
}

OasisMeas Oasis::extrapolatedBackSum() {
  OasisMeas sum = 0;
  for (auto row: m_rows) {
    sum += extrapolateBackDiff(aoc_debug(row));
    aoc_debug(sum);
    aoc_debug("");
    continue;
  }
  return sum;
}

bool getDiffVec(std::vector<OasisMeas> &in, std::vector<OasisMeas> &out) {
  OasisMeas last, delta;
  bool first = true;
  bool allzero = true;
  for (auto cur: in) {
    if (first) first = false; else {
      delta = cur - last;
      out.push_back(delta);
      if (delta) allzero = false;
    }
    last = cur;
  }
  aoc_debug(out);
  return allzero;
}

OasisMeas extrapolateDiff(std::vector<OasisMeas> &x) {
  std::vector<OasisMeas> tmp;
  if (getDiffVec(x, tmp)) return aoc_debug(x.back());
  else return aoc_debug(x.back() + extrapolateDiff(tmp));
}

OasisMeas extrapolateBackDiff(std::vector<OasisMeas> &x) {
  std::vector<OasisMeas> tmp;
  if (getDiffVec(x, tmp)) return aoc_debug(x.front());
  else return aoc_debug(x.front() - extrapolateBackDiff(tmp));
}
