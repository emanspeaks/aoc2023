#include "schematic.h"

void Schematic::parseLine(const std::string &s) {
  static int y = 0;
  Coord tmp = {0, y++};
  for (auto c: s) {
    m_grid.safeSet(tmp, c);
    tmp[0]++;
  }
}

int Schematic::search_perimeter(int x0, int x1, int y) {
  std::string s;
  char c;
  bool found = false;
  std::vector<int> gears;
  for (int yi = y - 1; yi <= y + 1; yi++) for (int x = x0 - 1; x <= x1 + 1; x++) {
    c = m_grid.safeGet(x, yi);
    if (yi == y && x >= x0 && x <= x1) s.push_back(c);
    else if (!(c == BLANKCHAR || is_numeric(c))) {
      found = true;
      if (c == GEARCHAR) gears.push_back(m_grid.xy2index(x, yi));
    }
    // if (found && yi > y) break;
  }
  int i = aoc_debug(std::stoi(s));
  for (auto g: gears) m_gearmap[g].push_back(i);
  return (found)? i : 0;
}

int Schematic::searchGrid(int &gearsum) {
  int mx, px, my, py;
  char c;

  m_grid.getActualExtents(mx, px, my, py);
  int numx0 = mx - 1, sum = 0;
  for (int y = my; y <= py + 1; y++) {
    if (numx0 >= mx) sum += search_perimeter(numx0, px, y - 1);
    if (y > py) break;

    numx0 = mx - 1;
    for (int x = mx; x <= px; x++) {
      c = m_grid.safeGet(x, y);
      if (is_numeric(c)) {
        if (numx0 < mx) numx0 = x;
      } else if (numx0 >= mx) {
        sum += search_perimeter(numx0, x - 1, y);
        numx0 = mx - 1;
      }
    }
  }
  calc_gears(gearsum);
  return sum;
}

void Schematic::calc_gears(int &gearsum) {
  for (auto i: m_gearmap) if (i.second.size() == 2) gearsum += aoc_debug(i.second[0]*i.second[1]);
}
