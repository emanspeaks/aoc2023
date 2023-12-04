#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "timing.h"

template <class HashType, class DistType>
class GraphNode {
  public:
    virtual HashType hash() = 0;
    virtual DistType costToNode(GraphNode<HashType, DistType> x) = 0;
    virtual std::unordered_set<GraphNode> getNeighbors() = 0;
};

template <class HashType, class DistType>
using GraphNodePath = std::deque<GraphNode<HashType, DistType>>;

template <class HashType, class DistType>
using NodeMap = std::unordered_map<HashType, GraphNode<HashType, DistType>>;

template <class HashType, class DistType>
class AStar {
  public:
    virtual DistType h(GraphNode<HashType, DistType> x) = 0;

    GraphNodePath<HashType, DistType> shortestPath(
      GraphNode<HashType, DistType> node_0,
      GraphNode<HashType, DistType> node_f
    ) {
      DistType gtmp;
      GraphNode<HashType, DistType> node = node_0;

      NodeMap<HashType, DistType> cameFrom, nmap;
      std::unordered_map<HashType, DistType> f, g;
      auto fcompare = [&](const HashType &a, const HashType &b) {
        return f[a] > f[b];
      };
      std::priority_queue<HashType, std::vector<HashType>, decltype(fcompare)> openq(fcompare);
      std::unordered_set<HashType> openset;

      HashType current = node.hash();
      nmap[current] = node;
      g[current] = 0;
      f[current] = h(node);
      openq.push(current);
      openset.insert(current);

      HashType newhash;
      int iters = 0;
      std::unordered_set<GraphNode> neighborhood;
      Epoch begin = tic();
      while (!openq.empty()) {
        if (!(++iters % 1000)) aoc_debug("iter check: " + std::to_string(iters));

        current = openq.top();
        openset.erase(current);
        openq.pop();
        node = nmap[current];

        if (node == node_f) return reconstructPath(cameFrom, node);

        neighborhood = node.getNeighbors();
        for (auto neighbor: neighborhood) {
          gtmp = g[current] + node.costToNode(neighbor); // "distance" is fixed as 1 min
          newhash = node.hash();
          if (!g.count(newhash) || gtmp < g[newhash]) {
            nmap[newhash] = neighbor;
            cameFrom[newhash] = node;
            g[newhash] = gtmp;
            f[newhash] = gtmp + h(neighbor);
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
      NodeMap<HashType, DistType> cameFrom,
      GraphNode<HashType, DistType> end
    ) {
      GraphNodePath<HashType, DistType> path;
      GraphNode<HashType, DistType> x = end;
      path.push_front(end);
      while (cameFrom.contains(x.hash())) {
        x = cameFrom[x];
        path.push_front(x);
      }
      return path;
    }
};
