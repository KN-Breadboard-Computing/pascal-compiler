#ifndef BBLOCKS_BB_CONTROL_FLOW_GRAPH_HPP
#define BBLOCKS_BB_CONTROL_FLOW_GRAPH_HPP

#include <algorithm>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../ast/program_node.hpp"
#include "../context/context.hpp"
#include "basic_block.hpp"

#undef CFG_DEBUG

namespace bblocks {
class BBControlFlowGraph {
 public:
  BBControlFlowGraph() = default;

  explicit BBControlFlowGraph(const std::string& entryLabel) : entryLabel_{entryLabel}, exitLabel_{entryLabel} { addBBlock(entryLabel, BasicBlock{}); }

  explicit BBControlFlowGraph(const std::string& entryLabel, BasicBlock basicBlock) : entryLabel_{entryLabel}, exitLabel_{entryLabel} { addBBlock(entryLabel, std::move(basicBlock)); }

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
  [[nodiscard]] std::map<std::string, BasicBlock>& basicBlocks() { return basicBlocks_; }
  [[nodiscard]] const BasicBlock& getBasicBlock(const std::string& blockLabel) const { return basicBlocks_.at(blockLabel); }
  void setBasicBlock(const std::string& blockLabel, BasicBlock block) { basicBlocks_[blockLabel] = block; }
  [[nodiscard]] BasicBlock& basicBlock(const std::string& blockLabel) { return basicBlocks_.at(blockLabel); }
  [[nodiscard]] const std::vector<std::string>& getOutLinks(const std::string& blockLabel) const { return srcDest_.at(blockLabel); }
  [[nodiscard]] const std::vector<std::string>& getInLinks(const std::string& blockLabel) const { return destSrc_.at(blockLabel); }
  [[nodiscard]] const std::map<std::string, std::vector<std::string>>& getSrcDestLinks() const { return srcDest_; }
  [[nodiscard]] const std::map<std::string, std::vector<std::string>>& getDestSrcLinks() const { return destSrc_; }

  void merge(const BBControlFlowGraph& cfg, const std::string& attachPoint, const std::string& cfgAttachPoint);
  void merge(const BBControlFlowGraph& cfg, const std::string& attachPoint);
  void merge(const BBControlFlowGraph& cfg);

  void update(const std::map<std::string, std::vector<std::string>>& srcDest, const std::map<std::string, std::vector<std::string>>& destSrc, const std::map<std::string, BasicBlock>& basicBlocks) {
    srcDest_ = std::move(srcDest);
    destSrc_ = std::move(destSrc);
    basicBlocks_ = std::move(basicBlocks);
  }

  std::size_t distance(const std::string& from, const std::string& to) const;

  friend std::ostream& operator<<(std::ostream& out, const BBControlFlowGraph& cfg);

  void removeEmptyBasicBlocks();
  void removeSingleUseAssignments(bool onlyTemporaries);

 private:
  struct VariableReassignment {
    BBInstruction::TemplateArgumentType type;
    NumericType number;
    VariableType variable;
  };

  std::string entryLabel_;
  std::string exitLabel_;
  std::map<std::string, BasicBlock> basicBlocks_;
  std::map<std::string, std::vector<std::string>> srcDest_;
  std::map<std::string, std::vector<std::string>> destSrc_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CONTROL_FLOW_GRAPH_HPP
