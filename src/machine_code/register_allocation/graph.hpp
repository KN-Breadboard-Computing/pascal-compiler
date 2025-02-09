#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace machine_code {
class Graph {
 public:
  Graph() = default;

  Graph(const Graph&) = default;
  Graph(Graph&&) = default;

  Graph& operator=(const Graph&) = default;
  Graph& operator=(Graph&&) = default;

  ~Graph() = default;

  std::size_t getVerticesNumber() const { return adjacencyList_.size(); }
  std::size_t getEdgesNumber() const {
    std::size_t edgesNumber{0};
    for (const auto& [vertex, neighbours] : adjacencyList_) {
      edgesNumber += neighbours.size();
    }
    return edgesNumber / 2;
  }

  std::vector<std::string> getVertices() const;
  std::vector<std::pair<std::string, std::string>> getEdges() const;

  void addVertex(const std::string& name);
  void addEdge(const std::string vertex1Name, const std::string vertex2Name);

  void removeVertex(const std::string& name);
  void removeEdge(const std::string& vertex1Name, const std::string& vertex2Name);

  [[nodiscard]] bool searchEdge(const std::string vertex1Name, const std::string vertex2Name) const;
  [[nodiscard]] std::size_t getDegree(const std::string& vertexName) const;
  [[nodiscard]] const std::vector<std::string>& getNeighbours(const std::string& vertexName) const {
    return adjacencyList_.at(vertexName);
  }

  friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

 private:
  std::map<std::string, std::vector<std::string>> adjacencyList_;
};
}  // namespace machine_code

#endif  // GRAPH_HPP