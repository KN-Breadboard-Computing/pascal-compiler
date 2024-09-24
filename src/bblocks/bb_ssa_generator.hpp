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

  void optimize();

 private:
  std::string appendVariableCounter(const std::string& var, size_t index);
  std::string removeVariableCounter(const std::string& var);
  void renameVariables(BBControlFlowGraph& cfg, const std::map<std::string, std::vector<std::string>>& dominanceTree,
                       const std::string& blockLabel, std::map<std::string, size_t>& variablesCounter,
                       std::map<std::string, std::stack<std::string>>& variableRenames,
                       std::map<std::string, std::vector<std::string>>& phis);

  std::map<std::string, BBControlFlowGraph> functionControlFlowGraphs_;
};
}  // namespace bblocks

#endif  // BB_SSA_GENERATOR_HPP