#include "digplan.h"

void DigPlan::parseLine(const std::string &s) {
  StrVec svec = tokenize_string(s);
  DigInstruction tmp;
  switch (s[0]) {
    case 'R': tmp.head = Heading::east; break;
    case 'L': tmp.head = Heading::west; break;
    case 'U': tmp.head = Heading::north; break;
    case 'D': tmp.head = Heading::south; break;
  }
  tmp.dist = std::stoi(svec[1]);
  tmp.hexdist = std::stoi(svec[2].substr(2, 5), nullptr, 16);
  switch (svec[2][7]) {
    case '0': tmp.hexhead = Heading::east; break;
    case '1': tmp.hexhead = Heading::south; break;
    case '2': tmp.hexhead = Heading::west; break;
    case '3': tmp.hexhead = Heading::north; break;
  }
  m_instr.push_back(tmp);
}

int DigPlan::simpleLagoonArea() {
  Coord xy{0, 0};
  m_grid.safeSet(xy, true);
  for (auto instr: m_instr) for (int i = 0; i < instr.dist; i++) m_grid.safeSet(xy = getNextCoord(xy, instr.head), true);

  int mx, px, my, py;
  m_grid.getActualExtents(mx, px, my, py);
  bool inside = false, up = false, down = false, v;
  int sum = 0;
  for (int y = my; y <= py; y++) {
    for (int x = mx; x <= px; x++) {
      v = m_grid.safeGet(x, y);
      if (v) {
        if (v && m_grid.safeGet(x, y - 1)) up = !up;
        if (v && m_grid.safeGet(x, y + 1)) down = !down;
        inside = up || down;
        sum++;
      } else if (inside) {
        sum++;
      }
    }
  }

  return sum;
}
