#include "astroplate.h"

void AstroPlate::parseLine(const std::string &s) {
  int count = 0;
  static int y = 0;
  Coord tmp = {-1, y++};
  for (auto c: s) {
    tmp[0]++;
    if (c == GALAXYCHAR) {
      m_plate.safeSet(tmp, 1);
      m_coords.push_back(tmp);
      count++;
    }
  }
  if (!count) m_blankrow.push_back(tmp[1]);
}

void AstroPlate::expandCols() {
  int count;
  for (int x = m_plate.mx(); x <= m_plate.px(); x++) {
    count = 0;
    for (int y = m_plate.my(); y <= m_plate.py(); y++) if (m_plate.safeGet(x, y)) count++;
    if (!count) {
      // m_plate.insertColumn(x);
      // for (auto &g: m_coords) if (g[0] > x) g[0]++;
      // x++;
      m_blankcol.push_back(x);
    }
  }
}

long long AstroPlate::totalMinDist(int scalar) {
  m_plate.debugGrid();
  long long sum = 0, dx, dy;
  int minx, maxx, miny, maxy;
  for (int a = 0; a < m_coords.size() - 1; a++) for (int b = a + 1; b < m_coords.size(); b++) {
    minx = std::min(m_coords[a][0], m_coords[b][0]);
    maxx = std::max(m_coords[a][0], m_coords[b][0]);
    miny = std::min(m_coords[a][1], m_coords[b][1]);
    maxy = std::max(m_coords[a][1], m_coords[b][1]);
    // dx = abs(m_coords[a][0] - m_coords[b][0]);
    // dy = abs(m_coords[a][1] - m_coords[b][1]);
    dx = dy = 0;
    for (int x = minx; x < maxx; x++) dx += (std::ranges::find(m_blankcol, x) != m_blankcol.end())? scalar : 1;
    for (int y = miny; y < maxy; y++) dy += (std::ranges::find(m_blankrow, y) != m_blankrow.end())? scalar : 1;
    sum += dx + dy;
  }

  return sum;
}
