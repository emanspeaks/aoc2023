#include "pipemap.h"

PipeOpening char2open(const char c) {
  switch (c) {
    // | is a vertical pipe connecting north and south.
    case '|': return PipeOpening::vert;
    // - is a horizontal pipe connecting east and west.
    case '-': return PipeOpening::horiz;
    // L is a 90-degree bend connecting north and east.
    case 'L': return PipeOpening::ne;
    // J is a 90-degree bend connecting north and west.
    case 'J': return PipeOpening::nw;
    // 7 is a 90-degree bend connecting south and west.
    case '7': return PipeOpening::sw;
    // F is a 90-degree bend connecting south and east.
    case 'F': return PipeOpening::se;
    case 'S': return PipeOpening::start;
    default: return PipeOpening::noopen;
  }
}

void PipeMap::parseLine(const std::string &s) {
  std::string tmp;
  int startidx = -1;
  for (int i = 0; i < s.length(); i++) {
    tmp += char2open(s[i]);
    if (s[i] == 'S') startidx = i;
  }
  Coord last = m_grid.parseLine(tmp);
  if (startidx >= 0) {
    last[0] = startidx;
    m_start = last;
  }
}

void PipeMap::debugGrid() {
  #ifdef AOCDEBUG
    char v;
    std::string c;
    int mx, px, my, py;
    m_grid.getActualExtents(mx, px, my, py);
    for (int y = my; y <= py; y++) {
      for (int x = mx; x <= px; x++) {
        v = m_grid.safeGet(x, y);
        switch (v) {
          // https://en.wikipedia.org/wiki/Box-drawing_character#Box_Drawing
          case PipeOpening::vert:   {c = u8"│"; break;}
          case PipeOpening::horiz:  {c = u8"─"; break;}
          case PipeOpening::ne:     {c = u8"└"; break;}
          case PipeOpening::nw:     {c = u8"┘"; break;}
          case PipeOpening::sw:     {c = u8"┐"; break;}
          case PipeOpening::se:     {c = u8"┌"; break;}
          case PipeOpening::start:  {c = u8"S"; break;}
          case PipeOpening::noopen: {c = u8"."; break;}
        }
        std::cout << c;
      }
      std::cout << "\n";
    }
    aoc_debug(m_start);
  #endif
}

int PipeMap::maxDist() {
  PipeOpening last1, last2;
  inferStart(last1, last2);

  Coord next1, next2;
  next1 = next2 = m_start;

  int dist = -1;
  m_isloop.safeSet(m_start, true);
  while (!++dist || next1 != next2) {
    next1 = getNextPipe(next1, last1);
    m_isloop.safeSet(next1, true);
    next2 = getNextPipe(next2, last2);
    m_isloop.safeSet(next2, true);

  }
  return dist;
}

int PipeMap::enclosedArea() {
  m_isloop.debugGrid();
  int mx, px, my, py;
  m_isloop.getActualExtents(mx, px, my, py);
  bool inside = false, up = false, down = false;
  int sum = 0;
  char v;
  for (int y = my; y <= py; y++) {
    for (int x = mx; x <= px; x++) {
      if (m_isloop.safeGet(x, y)) {
        v = m_grid.safeGet(x, y);
        if (v & PipeOpening::north) up = !up;
        if (v & PipeOpening::south) down = !down;
        inside = up || down;
      } else if (inside) {
        sum++;
      }
    }
  }
  return sum;
}

char invertDir(char old) {
  return (old > 0)*(old ^ (vert << 2*(old > vert)));
}

void PipeMap::inferStart(PipeOpening &last1, PipeOpening &last2) {
  char v = 0, tmp = 1;
  const int x = m_start[0], y = m_start[1];
  v |= invertDir(m_grid.safeGet(x + 1, y) & PipeOpening::west);
  v |= invertDir(m_grid.safeGet(x - 1, y) & PipeOpening::east);
  v |= invertDir(m_grid.safeGet(x, y + 1) & PipeOpening::north);
  v |= invertDir(m_grid.safeGet(x, y - 1) & PipeOpening::south);

  while (!(tmp & v)) tmp <<= 1;
  last1 = (PipeOpening)tmp;
  tmp <<= 1;

  while (!(tmp & v)) tmp <<= 1;
  last2 = (PipeOpening)tmp;

  m_grid.safeSet(m_start, v);
  debugGrid();
}

Coord PipeMap::getNextPipe(Coord c, PipeOpening &last) {
  Coord newc = c;
  switch (last) {
    case PipeOpening::west:  {newc[0]--; break;}
    case PipeOpening::east:  {newc[0]++; break;}
    case PipeOpening::north: {newc[1]--; break;}
    case PipeOpening::south: {newc[1]++; break;}
  }
  char v = m_grid.safeGet(newc);
  last = (PipeOpening)(v ^ invertDir(last));
  return newc;
}

/*
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
*/
