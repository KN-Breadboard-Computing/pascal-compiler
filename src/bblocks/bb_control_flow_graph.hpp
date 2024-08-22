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
  explicit BBControlFlowGraph(const std::string& entryLabel) : entryLabel_{entryLabel}, exitLabel_{entryLabel} {
    addBBlock(entryLabel, BasicBlock{});
  }

  BBControlFlowGraph(const BBControlFlowGraph&) = default;
  BBControlFlowGraph(BBControlFlowGraph&&) = default;

  BBControlFlowGraph& operator=(const BBControlFlowGraph&) = default;
  BBControlFlowGraph& operator=(BBControlFlowGraph&&) = default;

  virtual ~BBControlFlowGraph() = default;

  void addBBlock(const std::string& label, BasicBlock basicBlock);
  void addBlocksLink(const std::string& fromLabel, const std::string& toLabel);

  void setEntryLabel(const std::string& entryLabel) {
#ifdef BB_DEBUG
    std::cout << "New entry label: " << entryLabel << std::endl;
#endif
    entryLabel_ = entryLabel;
  }
  void setExitLabel(const std::string& exitLabel) {
#ifdef BB_DEBUG
    std::cout << "New exit label: " << exitLabel << std::endl;
#endif
    exitLabel_ = exitLabel;
  }

  [[nodiscard]] const std::string& getEntryLabel() const { return entryLabel_; }
  [[nodiscard]] const std::string& getExitLabel() const { return exitLabel_; }
  [[nodiscard]] const std::map<std::string, BasicBlock>& getBasicBlocks() const { return basicBlocks_; }
  [[nodiscard]] const BasicBlock& getBasicBlock(const std::string& blockLabel) { return basicBlocks_.at(blockLabel); }
  [[nodiscard]] const std::vector<std::string>& getOutLinks(const std::string& blockLabel) const {
    return srcDest_.at(blockLabel);
  }
  [[nodiscard]] const std::vector<std::string>& getInLinks(const std::string& blockLabel) const {
    return destSrc_.at(blockLabel);
  }

  void merge(const BBControlFlowGraph& cfg, const std::string& attachPoint, const std::string& cfgAttachPoint);
  void merge(const BBControlFlowGraph& cfg, const std::string& attachPoint);
  void merge(const BBControlFlowGraph& cfg);

  friend std::ostream& operator<<(std::ostream& out, const BBControlFlowGraph& cfg);

 private:
  std::string entryLabel_;
  std::string exitLabel_;
  std::map<std::string, BasicBlock> basicBlocks_;
  std::map<std::string, std::vector<std::string>> srcDest_;
  std::map<std::string, std::vector<std::string>> destSrc_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CONTROL_FLOW_GRAPH_HPP
