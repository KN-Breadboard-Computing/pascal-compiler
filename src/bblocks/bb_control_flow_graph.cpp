#include "bb_control_flow_graph.hpp"

#include <queue>
#include <set>

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

std::size_t BBControlFlowGraph::distance(const std::string& from, const std::string& to) const {
  std::queue<std::string> labels;
  std::map<std::string, std::size_t> distances;

  labels.push(from);
  distances.insert({from, 0});

  while (!labels.empty()) {
    const auto label = labels.front();
    labels.pop();
    for (const auto& neighbour : srcDest_.at(label)) {
      if (distances.find(neighbour) == distances.end()) {
        labels.push(neighbour);
        distances.insert({neighbour, distances.at(label) + 1});
      }
    }
  }

  return distances.at(to);
}

std::ostream& operator<<(std::ostream& out, const BBControlFlowGraph& cfg) {
  std::queue<std::string> labels;
  std::set<std::string> visited;

  labels.push(cfg.getEntryLabel());
  visited.insert(cfg.getEntryLabel());

  while (!labels.empty()) {
    const auto label = labels.front();
    labels.pop();
    if (cfg.destSrc_.find(label) != cfg.destSrc_.end()) {
      for (const auto& neighbour : cfg.destSrc_.at(label)) {
        out << neighbour << " ";
      }
      out << "-> ";
    }
    out << label;
    if (cfg.srcDest_.find(label) != cfg.srcDest_.end()) {
      out << " -> ";
      for (const auto& neighbour : cfg.srcDest_.at(label)) {
        out << neighbour << " ";
        if (visited.find(neighbour) == visited.end()) {
          labels.push(neighbour);
          visited.insert(neighbour);
        }
      }
    }
    out << "{" << std::endl << cfg.basicBlocks_.at(label) << "}" << std::endl << std::endl;
  }

  return out;
}
}  // namespace bblocks
