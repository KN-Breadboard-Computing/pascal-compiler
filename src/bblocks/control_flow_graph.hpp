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

  ControlFlowGraph(const ControlFlowGraph&) = delete;
  ControlFlowGraph(ControlFlowGraph&&) = default;

  ControlFlowGraph& operator=(const ControlFlowGraph&) = delete;
  ControlFlowGraph& operator=(ControlFlowGraph&&) = default;

  virtual ~ControlFlowGraph() = default;

  friend std::ostream& operator<<(std::ostream& out, const std::map<std::string, ControlFlowGraph>& cfgs) {
    for (const auto& [name, cfg] : cfgs) {
      out << "Control Flow Graph: " << name << std::endl;
      for (const auto& basicBlock : cfg.basicBlocks_) {
        out << *basicBlock;
      }
    }
    return out;
  }

 private:
  std::vector<std::unique_ptr<BasicBlock>> basicBlocks_;
  std::map<std::string, std::vector<std::string>> edges_;
};
}  // namespace bblocks

#endif  // BBLOCKS_CONTROL_FLOW_GRAPH_HPP
