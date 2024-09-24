#ifndef MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP
#define MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <fstream>

#include "../bblocks/bb_control_flow_graph.hpp"
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
  MachineInstruction generate(const std::unique_ptr<bblocks::BBInstruction>& instruction);

  std::map<std::string, std::vector<MachineInstruction>> machineCode_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP