#ifndef BB_SSA_GENERATOR_HPP
#define BB_SSA_GENERATOR_HPP

#include <algorithm>
#include <iterator>
#include <queue>
#include <set>
#include <stack>

#include "bb_control_flow_graph.hpp"
#include "instructions/bb_phi.hpp"

namespace bblocks {
class BbSsaGenerator {
 public:
  BbSsaGenerator() = default;

  BbSsaGenerator(const BbSsaGenerator&) = delete;
  BbSsaGenerator(BbSsaGenerator&&) = default;

  BbSsaGenerator& operator=(const BbSsaGenerator&) = delete;
  BbSsaGenerator& operator=(BbSsaGenerator&&) = default;

  virtual ~BbSsaGenerator() = default;

  [[nodiscard]] std::map<std::string, BBControlFlowGraph> getControlFlowGraphs() const { return functionControlFlowGraphs_; }

  void toSsa(const std::string& name, const BBControlFlowGraph& graph);
  void fromSsa();

  void removeRedundantAssignments();
  void propagateConstants();

 private:
  static std::string appendVariableCounter(const std::string& var, std::size_t index);
  static std::string removeVariableCounter(const std::string& var);
  void renameVariables(const std::string& blockLabel, BBControlFlowGraph& cfg,
                       const std::map<std::string, std::vector<std::string>>& dominanceTree,
                       std::map<std::string, std::size_t>& variableCounters,
                       std::map<std::string, std::stack<std::size_t>>& variableStacks,
                       std::map<std::string, std::map<std::string, std::map<std::string, std::size_t>>>& phiCompletions);

  std::map<std::string, BBControlFlowGraph> functionControlFlowGraphs_;
  std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::size_t>>>> phiCompletions_;
};
}  // namespace bblocks

#endif  // BB_SSA_GENERATOR_HPP