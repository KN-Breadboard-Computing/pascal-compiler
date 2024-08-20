#ifndef BBLOCKS_BB_CONTROL_FLOW_GRAPH_HPP
#define BBLOCKS_BB_CONTROL_FLOW_GRAPH_HPP

#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../ast/program_node.hpp"
#include "basic_block.hpp"

namespace bblocks {
class BBControlFlowGraph {
 public:
  BBControlFlowGraph() = default;

  BBControlFlowGraph(const BBControlFlowGraph&) = default;
  BBControlFlowGraph(BBControlFlowGraph&&) = default;

  BBControlFlowGraph& operator=(const BBControlFlowGraph&) = default;
  BBControlFlowGraph& operator=(BBControlFlowGraph&&) = default;

  virtual ~BBControlFlowGraph() = default;

  void addBBlock(const std::string& label, BasicBlock basicBlock) { basicBlocks_.insert({label, std::move(basicBlock)}); }

  void addBlocksLink(const std::string& label1, const std::string& label2) {
    if (edges_.find(label1) == edges_.end()) {
      edges_.insert({label1, {label2}});
    }
    else {
      edges_[label1].emplace_back(label2);
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const std::map<std::string, BBControlFlowGraph>& cfgs) {
    for (const auto& [name, cfg] : cfgs) {
      out << "Control Flow Graph: " << name << std::endl;
      for (const auto& basicBlock : cfg.basicBlocks_) {
        out << basicBlock.first;
        if (cfg.edges_.find(basicBlock.first) != cfg.edges_.end()) {
          out << " -> ";
          for (const auto& neighbour : cfg.edges_.at(basicBlock.first)) {
            out << neighbour << " ";
          }
        }
        out << std::endl << basicBlock.second << std::endl;
      }
    }
    return out;
  }

 private:
  std::map<std::string, BasicBlock> basicBlocks_;
  std::map<std::string, std::vector<std::string>> edges_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CONTROL_FLOW_GRAPH_HPP
