#pragma once

#include <string>
#include <unordered_map>

#include "aoc.h"

enum AlmSections {seed, soil, fert, water, light, temp, hum, loc};

typedef long long AlmIdx;

struct AlmRow {
  AlmIdx deststart = -1, srcstart = -1, blocklen = -1;
};

typedef std::vector<AlmRow> AlmTable;

struct AlmTblRange {
  AlmIdx min, max;

  AlmTblRange(): min(0), max(inf<AlmIdx>) {}
  AlmTblRange(int mn, int mx): min(mn), max(mx) {}
  AlmTblRange(AlmRow row, bool src = false): min((src)? row.srcstart : row.deststart),
    max(min + row.blocklen - 1) {}
};

class Almanac {
  public:
    void parseLine(const std::string &s);
    AlmIdx minLoc();
    AlmIdx seedRangesMinLoc();

  private:
    std::vector<AlmIdx> m_seeds;
    AlmTable m_tbls[8];
    std::vector<AlmTblRange> m_ranges[8];

    AlmIdx destLookup(AlmTable &tbl, AlmIdx src);
    AlmIdx calcMinLoc(std::vector<AlmIdx> &seedvec);
    AlmRow rowLookup(AlmTable &tbl, AlmIdx idx, bool buildifmissing = true, bool src = true);
    void srcToDestRanges(int srcidx);
};
