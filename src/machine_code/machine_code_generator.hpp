#ifndef MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP
#define MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP

#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "../bblocks/bb_control_flow_graph.hpp"
#include "live_ranges_generator.hpp"
#include "machine_instruction.hpp"

namespace machine_code {
class MachineCodeGenerator {
 public:
  MachineCodeGenerator() = default;

  MachineCodeGenerator(const MachineCodeGenerator&) = delete;
  MachineCodeGenerator(MachineCodeGenerator&&) = default;

  MachineCodeGenerator& operator=(const MachineCodeGenerator&) = delete;
  MachineCodeGenerator& operator=(MachineCodeGenerator&&) = default;

  ~MachineCodeGenerator() = default;

  void generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg);
  void saveMachineCode(const std::string& filename);
  void saveAssembly(const std::string& filename);

 private:
  void enumerateBlockLabels(const std::string& name, const bblocks::BBControlFlowGraph& cfg);
  MachineInstruction generate(const std::unique_ptr<bblocks::BBInstruction>& instruction);
  std::string getBinary(int number);

  std::map<std::string, std::map<std::string, std::pair<size_t, size_t>>> blockBounds_;
  std::map<std::string, std::vector<MachineInstruction>> machineCode_;
  std::map<std::string, LiveRangesGenerator> liveRanges_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP