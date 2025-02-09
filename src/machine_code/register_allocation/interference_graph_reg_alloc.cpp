#include "interference_graph_reg_alloc.hpp"

namespace machine_code {
void InterferenceGraphRegAlloc::allocateRegisters(const std::map<std::string, std::vector<LiveRange>>& liveRanges) {
  IntervalTree intervalTree{};
  for (const auto& [var, ranges] : liveRanges) {
    for (const auto& range : ranges) {
      intervalTree.insert(var, range.front().instructionEnumerator, range.back().instructionEnumerator);
    }
  }

  Graph interferenceGraph{};
  for (const auto& [var, ranges] : liveRanges) {
    std::vector<std::string> overlappingVariables;
    for (const auto& range : ranges) {
      intervalTree.overlaps(range.front().instructionEnumerator, range.back().instructionEnumerator, overlappingVariables);
    }

    for (const auto& neighbour : overlappingVariables) {
      if (var != neighbour) {
        interferenceGraph.addEdge(var, neighbour);
      }
    }
  }

  findColoring(interferenceGraph);
}

void InterferenceGraphRegAlloc::findColoring(Graph interferenceGraph) {
  Graph interferenceGraphCopy{interferenceGraph};
  std::stack<std::string> stack;
  while (interferenceGraphCopy.getVerticesNumber() > 0) {
    bool found = false;

    std::vector<std::string> vertices = interferenceGraphCopy.getVertices();
    for (const auto& vertex : vertices) {
      if (static_cast<int>(interferenceGraphCopy.getDegree(vertex)) < registersCount_) {
        stack.push(vertex);
        interferenceGraphCopy.removeVertex(vertex);
        found = true;
      }
    }

    if (!found) {
      std::string maxDegreeVertex;
      std::size_t maxDegree = 0;
      for (const auto& vertex : interferenceGraphCopy.getVertices()) {
        if (interferenceGraphCopy.getDegree(vertex) > maxDegree) {
          maxDegree = interferenceGraphCopy.getDegree(vertex);
          maxDegreeVertex = vertex;
        }
      }

      interferenceGraphCopy.removeVertex(maxDegreeVertex);
    }
  }

  std::set<int> usedColors;
  while (!stack.empty()) {
    const auto vertex = stack.top();
    stack.pop();

    usedColors.clear();
    for (const auto& neighbour : interferenceGraph.getNeighbours(vertex)) {
      if (allocatedRegisters_.find(neighbour) != allocatedRegisters_.end()) {
        usedColors.insert(allocatedRegisters_[neighbour]);
      }
    }

    int color = 1;
    for (const auto& usedColor : usedColors) {
      if (color != usedColor) {
        break;
      }
      ++color;
    }

    allocatedRegisters_[vertex] = color;
  }

  for (const auto& vertex : interferenceGraph.getVertices()) {
    if (allocatedRegisters_.find(vertex) == allocatedRegisters_.end()) {
      allocatedRegisters_[vertex] = -1;
    }
  }
}
}  // namespace machine_code