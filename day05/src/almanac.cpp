#include "almanac.h"

void Almanac::parseLine(const std::string &s) {
  static int sec = AlmSections::seed - 1;
  if (!is_numeric(s[0])) {
    if (sec < AlmSections::seed) {
      StrDeq sdeq = tokenize_string_deque(s);
      sdeq.pop_front();
      for (auto tok: sdeq) m_seeds.push_back(std::stoll(tok));
    }
    sec++;
  } else {
    StrVec svec = tokenize_string(s);

    AlmRow tmp = {std::stoll(svec[0]), std::stoll(svec[1]), std::stoll(svec[2])};
    m_tbls[sec].push_back(tmp);
  }
}

AlmIdx Almanac::destLookup(AlmTable &tbl, AlmIdx src) {
  AlmIdx delta;
  for (auto row: tbl) {
    delta = src - row.srcstart;
    if (delta < 0 || delta >= row.blocklen) continue;
    return row.deststart + delta;
  }
  return src;
}

AlmRow Almanac::rowLookup(AlmTable &tbl, AlmIdx idx, bool buildifmissing, bool src) {
  AlmIdx delta, upper = inf<AlmIdx>, lower = 0, start;
  for (auto row: tbl) {
    start = (src)? row.srcstart : row.deststart;
    delta = idx - start;
    if (delta < 0) upper = std::min(upper, start - 1);
    else if (delta >= row.blocklen) lower = std::max(lower, start + row.blocklen);
    else return row;
  }
  AlmRow tmp;
  if (buildifmissing) tmp = {lower, lower, upper - lower + 1};
  return tmp;
}

AlmIdx Almanac::minLoc() {
  return calcMinLoc(m_seeds);
}

AlmIdx Almanac::calcMinLoc(std::vector<AlmIdx> &seedvec) {
  std::vector<AlmIdx> loclist;
  AlmIdx tmp;
  for (auto seed: seedvec) {
    tmp = aoc_debug(seed);
    for (int i = 1; i < 8; i++)
      tmp = aoc_debug(destLookup(m_tbls[i], tmp));
    loclist.push_back(tmp);
  }
  return *std::ranges::min_element(loclist);
}

AlmIdx Almanac::seedRangesMinLoc() {
  // build rows for seed ranges
  AlmRow tmp;
  for (int i = 0; i < m_seeds.size(); i += 2) {
    tmp = {m_seeds[i], m_seeds[i], m_seeds[i + 1]};
    m_tbls[0].push_back(tmp);
    m_ranges[0].push_back(AlmTblRange(tmp));
  }

  bool found = false;
  while (!found) {
    found = true;
  }

  return 0;
}

void Almanac::srcToDestRanges(int srctbl) {
  std::vector<AlmTblRange> srcrng;
}
