#pragma once

#include <string>

#include "aoc.h"

class HeatLossMap {
  public:
    void parseLine(const std::string &s);
    int minHeatLoss();

  private:
    Grid<char> m_map;
};

typedef std::string HeatLossHash;
typedef int HeatLossDist;
typedef GraphNode<HeatLossHash, HeatLossDist> AbstractHeatLossNode;
typedef GraphNodePath<HeatLossHash, HeatLossDist> HeatLossPath;
typedef GraphNeighborList<HeatLossHash, HeatLossDist> HeatLossList;
typedef GraphNodePtr<HeatLossHash, HeatLossDist> AbstractHeatLossPtr;

class HeatLossNode: public AbstractHeatLossNode {
  public:
    Coord xy;

    HeatLossNode(Grid<char> &map, Coord xy, char head = 0, char headcount = 0, int step = 0):
      m_map(map), xy(xy), m_approachHead(head), m_approachCount(headcount), m_step(step) {}

    HeatLossHash hash() const override;
    HeatLossDist costToNode(const AbstractHeatLossPtr &x) const override;
    HeatLossList getNeighbors() const override;
    bool matches(const AbstractHeatLossPtr &other) const override;

  private:
    char m_approachHead, m_approachCount;
    Grid<char> &m_map;
    int m_step;
};

typedef std::shared_ptr<HeatLossNode> HeatLossPtr;

class HeatLossAStar: public AStar<HeatLossHash, HeatLossDist> {
  public:
    HeatLossDist h(const AbstractHeatLossPtr &x, const AbstractHeatLossPtr &node_f) const override;
};
