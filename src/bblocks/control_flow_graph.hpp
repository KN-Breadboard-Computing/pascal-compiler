#ifndef BBLOCKS_CONTROL_FLOW_GRAPH_HPP
#define BBLOCKS_CONTROL_FLOW_GRAPH_HPP

#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../ast/program_node.hpp"
#include "basic_block.hpp"

namespace bblocks {
class ControlFlowGraph {
 public:
  ControlFlowGraph() = default;

  ControlFlowGraph(const ControlFlowGraph&) = default;
  ControlFlowGraph(ControlFlowGraph&&) = default;

  ControlFlowGraph& operator=(const ControlFlowGraph&) = default;
  ControlFlowGraph& operator=(ControlFlowGraph&&) = default;

  virtual ~ControlFlowGraph() = default;

  friend std::ostream& operator<<(std::ostream& out, const ControlFlowGraph& cfg) {
    for (const auto& basicBlock : cfg.basicBlocks_) {
      out << *basicBlock;
    }
    return out;
  }

 private:
  std::vector<std::unique_ptr<BasicBlock>> basicBlocks_;
  std::map<std::string, std::vector<std::string>> edges_;
};
}  // namespace bblocks

#endif  // BBLOCKS_CONTROL_FLOW_GRAPH_HPP
