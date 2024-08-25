#include "bb_control_flow_graph.hpp"

namespace bblocks {
void BBControlFlowGraph::addBBlock(const std::string& label, BasicBlock basicBlock) {
#ifdef BB_DEBUG
  std::cout << "New basic block with label: " << label << std::endl;
#endif
  basicBlocks_.insert({label, std::move(basicBlock)});
  srcDest_.insert({label, {}});
  destSrc_.insert({label, {}});
}

void BBControlFlowGraph::addBlocksLink(const std::string& fromLabel, const std::string& toLabel) {
#ifdef BB_DEBUG
  std::cout << "New basic block link: " << fromLabel << " -> " << toLabel << std::endl;
#endif
  if (srcDest_.find(fromLabel) == srcDest_.end()) {
    srcDest_.insert({fromLabel, {toLabel}});
  }
  else {
    srcDest_[fromLabel].emplace_back(toLabel);
  }

  if (destSrc_.find(toLabel) == destSrc_.end()) {
    destSrc_.insert({toLabel, {fromLabel}});
  }
  else {
    destSrc_[toLabel].emplace_back(fromLabel);
  }
}

void BBControlFlowGraph::merge(const BBControlFlowGraph& cfg, const std::string& attachPoint, const std::string& cfgAttachPoint) {
  for (const auto& [label, basicBlock] : cfg.getBasicBlocks()) {
    addBBlock(label, basicBlock);
  }

  for (const auto& [src, dests] : cfg.srcDest_) {
    for (const auto& dest : dests) {
      addBlocksLink(src, dest);
    }
  }

#ifdef BB_DEBUG
  std::cout << "Merge " << cfgAttachPoint << " to " << attachPoint << std::endl;
#endif
  addBlocksLink(attachPoint, cfgAttachPoint);
}

void BBControlFlowGraph::merge(const BBControlFlowGraph& cfg, const std::string& attachPoint) {
  merge(cfg, attachPoint, cfg.getEntryLabel());
}

void BBControlFlowGraph::merge(const BBControlFlowGraph& cfg) {
  merge(cfg, exitLabel_, cfg.getEntryLabel());
}

std::ostream& operator<<(std::ostream& out, const BBControlFlowGraph& cfg) {
  for (const auto& basicBlock : cfg.basicBlocks_) {
    out << basicBlock.first;
    if (cfg.srcDest_.find(basicBlock.first) != cfg.srcDest_.end()) {
      out << " -> ";
      for (const auto& neighbour : cfg.srcDest_.at(basicBlock.first)) {
        out << neighbour << " ";
      }
    }
    out << "{" << std::endl << basicBlock.second << "}" << std::endl << std::endl;
  }

  return out;
}
}  // namespace bblocks
