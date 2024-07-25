#include <stack>

#include "polygon.h"

Edge::Edge(Vertex &p1, Vertex &p2) {
  points[0] = p1.hash();
  points[1] = p2.hash();
}

bool Edge::operator==(const Edge &other) const {
  return (
    (points[0] == other.points[0] || points[0] == other.points[1])
    && (points[1] == other.points[1] || points[1] == other.points[0])
  );
}

void Polygon::addEdgeFromPoints(Vertex v1, Vertex v2) {
  std::string hash1 = v1.hash(), hash2 = v2.hash();
  if (!m_points.contains(hash1)) m_points[hash1] = v1;
  if (!m_points.contains(hash2)) m_points[hash2] = v2;
  Vertex &p1 = m_points[hash1], &p2 = m_points[hash2];

  m_edges.push_back(std::make_unique<Edge>(p1, p2));
  p1.addEdge(m_edges.back().get());
  p2.addEdge(m_edges.back().get());
}

void Polygon::removeEdge(EdgeIt i) {
  Edge *e = (*i).get();
  m_points[e->points[0]].removeEdge(e);
  m_points[e->points[1]].removeEdge(e);
  m_edges.erase(i);
}

void Polygon::merge(Polygon &other) {
  std::stack<EdgeIt> thismatch;
  std::vector<Edge*> othermatch;
  bool found = false;
  for (auto i = m_edges.begin(); i != m_edges.end(); i++) {
    for (auto j = other.m_edges.begin(); j != other.m_edges.end(); j++)
      if ((*i).get() == (*j).get()) {thismatch.push(i); othermatch.push_back((*j).get()); found = true;}
  }

  while (!thismatch.empty()) {
    removeEdge(thismatch.top());
    thismatch.pop();
  }

  Edge *e;
  for (auto j = other.m_edges.begin(); j != other.m_edges.end(); j++) {
    e = (*j).get();
    if (std::ranges::find(othermatch, e) != othermatch.end()) continue;
    addEdgeFromPoints(
      other.m_points[e->points[0]],
      other.m_points[e->points[1]]
    );
  }

  // debug_print_edges();
  debug_print_point_edges();
}

Polygon::Polygon(Coord anchor, Coord delta) {
  Coord c1, c2, c3;
  c1 = c2 = c3 = anchor;
  // 01
  // 23
  c1[0] += delta[0];
  c2[1] += delta[1];
  c3[0] += delta[0];
  c3[1] += delta[1];
  Vertex v0(anchor), v1(c1), v2(c2), v3(c3);
  addEdgeFromPoints(v0, v1);
  addEdgeFromPoints(v0, v2);
  addEdgeFromPoints(v3, v1);
  addEdgeFromPoints(v3, v2);
  // debug_print_edges();
  debug_print_point_edges();
}

long long Polygon::area(std::string vp) const {
  // triangle formulation of Shoelace Formula
  Edge *ep0 = m_points.at(vp).edges[0], *ep = ep0;
  long long sum = 0;
  bool i;
  std::string v2p;
  do {
    i = ep->points[1] == vp;
    v2p = ep->points[!i];
    // aoc_debug(vp + " > " + v2p);
    sum += m_points.at(vp).xy[0]*m_points.at(v2p).xy[1] - m_points.at(vp).xy[1]*m_points.at(v2p).xy[0];
    vp = v2p;
    i = m_points.at(vp).edges[1] == ep;
    ep = m_points.at(vp).edges[!i];
  } while (ep != ep0);
  return sum/2;
}

long long Polygon::area(const Coord xy) const {
  return area(Vertex(xy).hash());
}

void Polygon::debug_print_edges() {
  #ifdef AOCDEBUG
    Edge *e;
    for (auto i = m_edges.begin(); i != m_edges.end(); i++) {
      aoc_debug(std::distance(m_edges.begin(), i));
      debug_print_single_edge((*i).get());
    }
    aoc_debug("");
  #endif
}

void Polygon::debug_print_point_edges() {
  #ifdef AOCDEBUG
    Edge *e;
    for (auto &[k, v]: m_points) {
      aoc_debug(k);
      debug_print_single_edge(v.edges[0]);
      debug_print_single_edge(v.edges[1]);
    }
    aoc_debug("");
  #endif
}

void debug_print_single_edge(Edge *e) {
  #ifdef AOCDEBUG
    aoc_debug(e->points[0] + " - " + e->points[1]);
  #endif
}
