#include "digplan.h"
#include "polygon.h"

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

/*  This is the version using grid counting...
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
*/

int DigPlan::simpleLagoonArea() {
  const Coord anchor{0, 0};
  Coord xy = anchor, newanchor, delta;
  Polygon p(anchor), ptmp;
  for (auto instr: m_instr) {
    newanchor = xy;
    delta = getNextCoord(anchor, instr.head);

    //always offset anchor by +1 along axis we are moving,
    //accounts for overlap when going negative
    newanchor[0] += !!delta[0];
    newanchor[1] += !!delta[1];

    // officially adjust the reference path
    delta[0] *= instr.dist;
    delta[1] *= instr.dist;
    xy[0] += delta[0];
    xy[1] += delta[1];
    aoc_debug(delta);

    // if dist is negative, move anchor backwards
    // note: if dist = -1, this puts us back where we started...
    if (!(instr.dist == 1 && instr.head & Heading::neg)) {
      newanchor[0] += delta[0]*(delta[0] < 0);
      newanchor[1] += delta[1]*(delta[1] < 0);

      // make delta be width/height
      delta[0] = abs(delta[0]);
      delta[1] = abs(delta[1]);

      // add one along axis we are not moving,
      // subtract one from the one we are moving to leave a space for the final box
      delta[0] += !delta[0] - !!delta[0];
      delta[1] += !delta[1] - !!delta[1];
      ptmp = Polygon(newanchor, delta);
      p.merge(ptmp);
    }
    // add final box
    ptmp = Polygon(xy);
    p.merge(ptmp);
  }

  return std::max(p.area(anchor), std::max(p.area(Coord{0, 1}), p.area(Coord{1, 1})));
}
