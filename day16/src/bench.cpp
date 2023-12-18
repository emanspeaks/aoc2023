#include <unordered_set>
#include <unordered_map>
#include <queue>

#include "bench.h"

void OpticalBench::parseLine(const std::string &s) {
  m_bench.parseLine(s);
}

int OpticalBench::initEnergized() {
  return propagate({{-1, 0}, Heading::east});
}

int OpticalBench::maxEnergized() {
  int mx, px, my, py, nrgmax = 0;
  m_bench.getActualExtents(mx, px, my, py);
  for (int x = mx; x <= px; x++) nrgmax = std::max(nrgmax, propagate({{x, my - 1}, Heading::south}));
  for (int x = mx; x <= px; x++) nrgmax = std::max(nrgmax, propagate({{x, py + 1}, Heading::north}));
  for (int y = my; y <= py; y++) nrgmax = std::max(nrgmax, propagate({{mx - 1, y}, Heading::east}));
  for (int y = my; y <= py; y++) nrgmax = std::max(nrgmax, propagate({{px + 1, y}, Heading::west}));
  return nrgmax;
}

int OpticalBench::propagate(HeadingState init) {
  std::vector<bool> nrgzd((m_bench.px() + 1)*(m_bench.py() + 1), false);
  std::unordered_set<std::string> visited;
  std::queue<std::string> paths;
  std::unordered_map<std::string, HeadingState> cache;
  HeadingState last(init), next;
  std::string hash = last.hash();
  paths.push(hash);
  cache[hash] = last;
  char c;
  while (!paths.empty()) {
    hash = paths.front();
    paths.pop();
    if (visited.contains(hash)) continue;
    last = cache[hash];
    visited.insert(hash);
    if (!m_bench.isCoordOutside(last.xy)) nrgzd[m_bench.coord2index(last.xy)] = true;
    next = last;
    next.xy = getNextCoord(last.xy, last.head);
    if (m_bench.isCoordOutside(next.xy)) continue;
    switch (m_bench.safeGet(next.xy)) {
      case FWDMIRROR: next.head ^= (char)Heading::all; break;
      case BWDMIRROR: next.head ^= (char)Heading::swap; break;

      case HORIZSPLIT:
        if (next.head & Heading::py) {
          last = next;
          last.head = Heading::east;
          hash = last.hash();
          paths.push(hash);
          cache[hash] = last;
          next.head = Heading::west;
        }
        break;

      case VERTSPLIT:
        if (next.head & Heading::px) {
          last = next;
          last.head = Heading::north;
          hash = last.hash();
          paths.push(hash);
          cache[hash] = last;
          next.head = Heading::south;
        }
        break;
    }
    hash = next.hash();
    paths.push(hash);
    cache[hash] = next;
  }
  return std::ranges::count(nrgzd, true);
}
