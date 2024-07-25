#pragma once

#include <string>
#include <unordered_map>
#include <list>

#include "aoc.h"

struct Vertex;

struct Edge {
  Edge(Vertex &p1, Vertex &p2);

  std::string points[2];

  bool operator==(const Edge &other) const;
};

typedef std::unique_ptr<Edge> EdgePtr;
typedef std::list<EdgePtr>::iterator EdgeIt;

struct Vertex {
  Vertex() = default;
  Vertex(Coord c): xy(c), edges{nullptr, nullptr} {}

  Coord xy;
  Edge *edges[2];  // assume non-self-intersecting polygon

  std::string hash() const {return std::to_string(xy[0]) + "," + std::to_string(xy[1]);}
  bool operator==(const Vertex &other) const {return xy == other.xy;}
  void addEdge(Edge *e) {if (!edges[0]) edges[0] = e; else edges[1] = e;}
  void removeEdge(Edge *e) {if (edges[0] && *e == *edges[0]) edges[0] = nullptr; else edges[1] = nullptr;}
};

class Polygon {
  public:
    Polygon() = default;
    Polygon(Coord anchor, Coord delta = {1, 1});
    void addEdgeFromPoints(Vertex v1, Vertex v2);
    void merge(Polygon &other);
    long long area(const Coord xy) const;

  private:
    std::unordered_map<std::string, Vertex> m_points;
    std::list<EdgePtr> m_edges;

    long long area(std::string vp) const;
    void removeEdge(EdgeIt i);
    void debug_print_edges();
    void debug_print_point_edges();
};

void debug_print_single_edge(Edge *e);
