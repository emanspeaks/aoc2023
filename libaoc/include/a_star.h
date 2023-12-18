#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "timing.h"

template <class HashType, class DistType>
class GraphNode {
  public:
    virtual HashType hash() const = 0;
    virtual DistType costToNode(const std::shared_ptr<GraphNode<HashType, DistType>> &x) const = 0;
    virtual std::vector<std::shared_ptr<GraphNode>> getNeighbors() const = 0;
    virtual bool matches(const std::shared_ptr<GraphNode<HashType, DistType>> &other) const = 0;
};

template <class HashType, class DistType>
using GraphNodePtr = std::shared_ptr<GraphNode<HashType, DistType>>;

template <class HashType, class DistType>
using GraphNeighborList = std::vector<GraphNodePtr<HashType, DistType>>;

template <class HashType, class DistType>
using GraphNodePath = std::deque<GraphNodePtr<HashType, DistType>>;

template <class HashType, class DistType>
using NodeMap = std::unordered_map<HashType, GraphNodePtr<HashType, DistType>>;

template <class HashType, class DistType>
class AStar {
  public:
    virtual DistType h(
      const GraphNodePtr<HashType, DistType> &x,
      const GraphNodePtr<HashType, DistType> &node_f
    ) const = 0;

    GraphNodePath<HashType, DistType> shortestPath(
      const GraphNodePtr<HashType, DistType> &node_0,
      const GraphNodePtr<HashType, DistType> &node_f
    ) const {
      DistType gtmp;
      GraphNodePtr<HashType, DistType> node = node_0;
      GraphNode<HashType, DistType> *nodeptr = node.get();

      NodeMap<HashType, DistType> cameFrom, nmap;
      std::unordered_map<HashType, DistType> f, g;
      auto fcompare = [&](const HashType &a, const HashType &b) {
        return f[a] > f[b];
      };
      std::priority_queue<HashType, std::vector<HashType>, decltype(fcompare)> openq(fcompare);
      std::unordered_set<HashType> openset;

      HashType current = nodeptr->hash();
      nmap[current] = node;
      g[current] = 0;
      f[current] = h(node, node_f);
      openq.push(current);
      openset.insert(current);

      HashType newhash;
      int iters = 0;
      GraphNeighborList<HashType, DistType> neighborhood;
      Epoch begin = tic();
      while (!openq.empty()) {
        if (!(++iters % 1000)) aoc_debug("iter check: " + std::to_string(iters));

        current = openq.top();
        openset.erase(current);
        openq.pop();
        node = nmap[current];
        nodeptr = node.get();

        if (nodeptr->matches(node_f)) return reconstructPath(cameFrom, node);

        neighborhood = nodeptr->getNeighbors();
        for (auto &neighbor: neighborhood) {
          gtmp = g[current] + nodeptr->costToNode(neighbor);
          newhash = neighbor.get()->hash();
          if (!g.count(newhash) || gtmp < g[newhash]) {
            nmap[newhash] = neighbor;
            cameFrom[newhash] = node;
            g[newhash] = gtmp;
            f[newhash] = gtmp + h(neighbor, node_f);
            if (openset.find(newhash) == openset.end()) {
              openq.push(newhash);
              openset.insert(newhash);
            }
          }
        }
      }
      return GraphNodePath<HashType, DistType>();
    }

  private:
    GraphNodePath<HashType, DistType> reconstructPath(
      NodeMap<HashType, DistType> &cameFrom,
      const GraphNodePtr<HashType, DistType> &end
    ) const {
      GraphNodePath<HashType, DistType> path;
      GraphNodePtr<HashType, DistType> x = end;
      HashType hash;
      path.push_front(end);
      while (cameFrom.contains(hash = x.get()->hash())) {
        x = cameFrom[hash];
        path.push_front(x);
      }
      return path;
    }
};
