#include <numeric>
#include <bit>

#include "springrecords.h"

void SpringRecords::parseLine(const std::string &s) {
  StrVec svec = tokenize_string(s), errvec = tokenize_string(svec[1], ',');
  m_rec.push_back(svec[0]);
  std::vector<int> tmp;
  for (auto x: errvec) tmp.push_back(std::stoi(x));
  m_damage.push_back(tmp);
}

unsigned long long SpringRecords::recPermCount() {
  unsigned long long sum = 0;
  for (int i = 0; i < m_rec.size(); i++) sum += aoc_debug(resolveRow(m_rec[i], m_damage[i]));
  return sum;
}

unsigned long long SpringRecords::foldedRecPermCount() {
  unsigned long long sum = 0;
  std::string tmp;
  std::vector<int> tmpdamage;
  for (int i = 0; i < m_rec.size(); i++) {
    tmp = m_rec[i];
    tmpdamage = m_damage[i];
    tmpdamage.reserve(5*m_damage[i].size());
    for (int j = 0; j < 4; j++) {
      tmp += UNKNOWN + m_rec[i];
      tmpdamage.insert(tmpdamage.end(), m_damage[i].begin(), m_damage[i].end());
    }
    aoc_debug(tmp);
    aoc_debug(tmpdamage);
    sum += aoc_debug(resolveRow(tmp, tmpdamage));
  }
  return sum;
}

unsigned long long resolveRow(std::string rec, std::vector<int> damage) {
  int nu = 0, nd = 0, td = std::reduce(damage.cbegin(), damage.cend());
  unsigned long long sum = 0;
  std::vector<int> singles;
  char last, last2;
  last = last2 = WORKING;
  for (int i = 0; i < rec.size(); i++) {
    if (rec[i] == UNKNOWN) nu++;
    else {
      if (last == UNKNOWN && last2 != UNKNOWN) singles.push_back(i - 1);
      if (rec[i] == DAMAGED) nd++;
    }
    last2 = last;
    last = rec[i];
  }
  // aoc_debug(nu);
  unsigned long long imax = ((long long)1 << nu) - 1;
  int k, q;
  std::vector<int> test;
  std::string tmp;
  bool indamage, failed;
  for (unsigned long long i = 1; i <= imax; i++) {
    if (!(i%50000000)) aoc_debug(i);
    if (std::popcount(i) != td - nd) continue;
    k = 0;
    tmp = rec;
    test.clear();
    test.reserve(damage.size());
    indamage = false,
    failed = false;
    for (int j = 0; j < tmp.length(); j++) {
      switch (tmp[j]) {
        case UNKNOWN: {
          tmp[j] = (i & ((long long)1 << k++))? DAMAGED : WORKING;
          j--;
          break;
        }
        case DAMAGED:
          if (indamage) {
            test.back()++;
            if (test.back() > damage[test.size() - 1]) {
              failed = true;
              break;
            }
          }
          else {
            test.push_back(1);
            if (test.size() > damage.size()) {
              failed = true;
              break;
            }
          }

        default:
          indamage = tmp[j] == DAMAGED;
      }
      if (failed) break;
    }
    if (damage == test) {
      if (singles.size()) {
        while (singles.size()) {
          q = singles.back();
          singles.pop_back();
          if (q && q < tmp.length() - 2 && tmp[q - 1] != tmp[q + 1]) {
            rec[q] = tmp[q];
            if (tmp[q] == DAMAGED) nd++;
            nu--;
          }
        }
        if (!nu) return 1;
        // aoc_debug("Singles reset");
        imax = ((long long)1 << nu) - 1;
        i = 0;
      } else sum++;
    }
  }
  return sum;
}
