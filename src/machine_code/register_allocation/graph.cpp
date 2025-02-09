#include "graph.hpp"

namespace machine_code {
void Graph::addVertex(const std::string& name) {
  adjacencyList_[name] = std::vector<std::string>{};
}

void Graph::addEdge(const std::string vertex1Name, const std::string vertex2Name) {
  if (!searchEdge(vertex1Name, vertex2Name)) {
    adjacencyList_[vertex1Name].push_back(vertex2Name);
    adjacencyList_[vertex2Name].push_back(vertex1Name);
  }
}

std::vector<std::string> Graph::getVertices() const {
  std::vector<std::string> vertices;
  for (const auto& [vertex, neighbours] : adjacencyList_) {
    vertices.push_back(vertex);
  }

  return vertices;
}

std::vector<std::pair<std::string, std::string>> Graph::getEdges() const {
  std::vector<std::pair<std::string, std::string>> edges;
  for (const auto& [vertex, neighbours] : adjacencyList_) {
    for (const auto& neighbour : neighbours) {
      edges.push_back({vertex, neighbour});
    }
  }

  return edges;
}

void Graph::removeVertex(const std::string& name) {
  adjacencyList_.erase(name);
  for (auto& [vertex, neighbours] : adjacencyList_) {
    neighbours.erase(std::remove(neighbours.begin(), neighbours.end(), name), neighbours.end());
  }
}

void Graph::removeEdge(const std::string& vertex1Name, const std::string& vertex2Name) {
  if (searchEdge(vertex1Name, vertex2Name)) {
    adjacencyList_[vertex1Name].erase(
        std::find(adjacencyList_[vertex1Name].begin(), adjacencyList_[vertex1Name].end(), vertex2Name));
    adjacencyList_[vertex2Name].erase(
        std::find(adjacencyList_[vertex2Name].begin(), adjacencyList_[vertex2Name].end(), vertex1Name));
  }
}

bool Graph::searchEdge(const std::string vertex1Name, const std::string vertex2Name) const {
  if (adjacencyList_.find(vertex1Name) == adjacencyList_.end()) {
    return false;
  }

  return std::find(adjacencyList_.at(vertex1Name).begin(), adjacencyList_.at(vertex1Name).end(), vertex2Name) !=
         adjacencyList_.at(vertex1Name).end();
}

std::size_t Graph::getDegree(const std::string& vertexName) const {
  return adjacencyList_.at(vertexName).size();
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
  for (const auto& [node, neighbours] : graph.adjacencyList_) {
    os << node << " -> ";
    for (const auto& neighbour : neighbours) {
      os << neighbour << " ";
    }
    os << std::endl;
  }

  return os;
}

}  // namespace machine_code