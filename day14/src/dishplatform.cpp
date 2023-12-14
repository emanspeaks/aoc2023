#include "dishplatform.h"

void DishPlatform::parseLine(const std::string &s) {
  // Coord last = m_platform.parseLine(s);
  m_height++;
  m_width = s.length();
  for (auto c: s) {
    m_round.push_back(c == ROUNDROCK);
    m_sq.push_back(c == SQUAREROCK);
  }
}

RockState DishPlatform::tiltNorth(const RockState &in) {
  RockState out(m_height*m_width, false);
  std::vector<int> laststop(m_width, -1);
  int x = -1, y = 0;
  for (int i = 0; i < m_height*m_width; i++) {
    if (++x == m_width) {y++; x = 0;}
    if (m_sq[i]) {laststop[x] = y; continue;}
    if (in[i]) out[xy2idx(x, ++laststop[x])] = true;
  }
  return out;
}

RockState DishPlatform::tiltSouth(const RockState &in) {
  RockState out(m_height*m_width, false);
  std::vector<int> laststop(m_width, m_height);
  int x = m_width, y = m_height - 1;
  for (int i = m_height*m_width - 1; i >= 0; i--) {
    if (--x == -1) {y--; x = m_width - 1;}
    if (m_sq[i]) {laststop[x] = y; continue;}
    if (in[i]) out[xy2idx(x, --laststop[x])] = true;
  }
  return out;
}

RockState DishPlatform::tiltWest(const RockState &in) {
  RockState out(m_height*m_width, false);
  std::vector<int> laststop(m_height, -1);
  int x = -1, y = 0;
  for (int i = 0; i < m_height*m_width; i++) {
    if (++x == m_width) {y++; x = 0;}
    if (m_sq[i]) {laststop[y] = x; continue;}
    if (in[i]) out[xy2idx(++laststop[y], y)] = true;
  }
  return out;
}

RockState DishPlatform::tiltEast(const RockState &in) {
  RockState out(m_height*m_width, false);
  std::vector<int> laststop(m_height, m_width);
  int x = m_width, y = m_height - 1;
  for (int i = m_height*m_width - 1; i >= 0; i--) {
    if (--x == -1) {y--; x = m_width - 1;}
    if (m_sq[i]) {laststop[y] = x; continue;}
    if (in[i]) out[xy2idx(--laststop[y], y)] = true;
  }
  return out;
}


int DishPlatform::initNorthBeamLoad() {
  RockState tmp = tiltNorth(m_round);
  debugPlatform(tmp);
  return northBeamLoad(tmp);
}

int DishPlatform::northBeamLoad(const RockState &in) {
  int sum = 0;
  for (int i = 0; i < m_height*m_width; i++) if (in[i]) sum += m_height - idx2coord(i)[1];
  return sum;
}

int DishPlatform::xy2idx(int x, int y) {
  return x + y*m_width;
}

Coord DishPlatform::idx2coord(int i) {
  int x = i % m_width;
  return Coord{x, i/m_width};
}

RockState DishPlatform::spinCycle(const RockState &in) {
  return debugPlatform(tiltEast(tiltSouth(tiltWest(tiltNorth(in)))));
}

int DishPlatform::fullSpinCycle() {
  RockState tmp = spinCycle(m_round);
  m_roundcycle.push_back(tmp);
  bool found = false;
  auto it = m_roundcycle.begin();
  while (!found) {
    tmp = spinCycle(tmp);
    it = std::ranges::find(m_roundcycle, tmp);
    found = it != m_roundcycle.end();
    if (!found) m_roundcycle.push_back(tmp);
  }
  int start = std::distance(m_roundcycle.begin(), it);
  int i = (CYCLES - start - 1) % (m_roundcycle.size() - start) + start;
  return northBeamLoad(m_roundcycle[i]);
}

const RockState &DishPlatform::debugPlatform(const RockState &round) const {
  #ifdef AOCDEBUG
    for (int i = 0; i < m_width*m_height; i++) {
      if (i && !(i % m_width)) std::cout << "\n";
      std::cout << ((m_sq[i])? SQUAREROCK : ((round[i])? ROUNDROCK : BLANKCHAR));
    }
    std::cout << "\n";
  #endif
  return round;
}
