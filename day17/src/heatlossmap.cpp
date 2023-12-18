#include "heatlossmap.h"

void HeatLossMap::parseLine(const std::string &s) {
  m_map.parseLine(s, '0');
}

int HeatLossMap::minHeatLoss() {
  Coord tmp{m_map.mx(), m_map.my()};
  HeatLossPtr init = std::make_shared<HeatLossNode>(m_map, tmp, Heading::east);
  HeatLossPtr final = std::make_shared<HeatLossNode>(m_map, Coord{m_map.px(), m_map.py()});
  HeatLossAStar astar;
  HeatLossPath path = astar.shortestPath(init, final);
  int sum = -m_map.safeGet(tmp);
  for (auto &x: path) {
    tmp = dynamic_cast<HeatLossNode*>(x.get())->xy;
    // aoc_debug(tmp);
    sum += m_map.safeGet(tmp);
  }
  return sum;
}

HeatLossDist HeatLossAStar::h(const AbstractHeatLossPtr &x, const AbstractHeatLossPtr &node_f) const {
  HeatLossNode *init = dynamic_cast<HeatLossNode*>(x.get()), *final = dynamic_cast<HeatLossNode*>(node_f.get());
  return abs(final->xy[0] - init->xy[0]) + abs(final->xy[1] - init->xy[1]);
}

HeatLossHash HeatLossNode::hash() const {
  return (
    std::to_string(xy[0])
    + "," + std::to_string(xy[1])
    + "," + std::to_string(m_step)
    + "," + std::to_string(m_approachHead)
  );
}

HeatLossDist HeatLossNode::costToNode(const AbstractHeatLossPtr &x) const {
  return m_map.safeGet(dynamic_cast<HeatLossNode*>(x.get())->xy);
}

HeatLossList HeatLossNode::getNeighbors() const {
  HeatLossList out;
  Coord next;
  for (char head: {
    m_approachHead,
    (char)(m_approachHead ^ Heading::swap),
    (char)(m_approachHead ^ Heading::swap ^ Heading::neg)
  }) {
    if (head == m_approachHead && m_approachCount == 3) continue;
    next = getNextCoord(xy, head);
    if (m_map.isCoordOutside(next)) continue;
    out.push_back(std::make_shared<HeatLossNode>(m_map, next, head, 1 + m_approachCount*(head == m_approachHead), m_step + 1));
  }
  // #ifdef AOCDEBUG
  //   std::cout << hash() << " -> ";
  //   for (auto &x: out) std::cout << x.get()->hash() << "; ";
  //   std::cout << "\n";
  // #endif
  return out;
}

bool HeatLossNode::matches(const AbstractHeatLossPtr &other) const {
  return xy == dynamic_cast<HeatLossNode*>(other.get())->xy;
}
